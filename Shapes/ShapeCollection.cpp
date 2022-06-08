#include "ShapeCollection.h"


const size_t buffCapacity = 1024;

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
		delete shapes[i];  
	delete[] shapes;
}
void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (size_t i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i]; 
	delete[] shapes;
	shapes = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(const Shape* shape)
{
	if (shapesCount == capacity)
		resize();
	shapes[shapesCount++] = shape->clone(); 
}

void ShapeCollection::erase(size_t i)
{
	if (i >= shapesCount)
	{
		outOfRangeMessage(i);
		return;
	}

	delete shapes[i];
	shapes[i] = shapes[shapesCount - 1];
	shapesCount--;
	std::cout << "Erased figure (" << i << ")!\n";
}

void ShapeCollection::translate(double vertical, double horizontal, int i)
{

	if (i == -1)
	{
		for (size_t j = 0; j < shapesCount; j++)
		{
			shapes[j]->translate(vertical, horizontal);
		}
		std::cout << "Translated all figures!\n";
		return;
	}

	if (i >= shapesCount) 
	{
		outOfRangeMessage(i);
		return;
	}

	shapes[i]->translate(vertical, horizontal);
	std::cout << "Translated figure " << i << "!\n";

}

void ShapeCollection::within(const Shape* s) const
{
	if (shapesCount == 0)
	{
		emptyArrayMessage();
		return;
	}

	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isShapeWithinShape(s))
			shapes[i]->print();
	}
}

void ShapeCollection::areas() const
{
	if (shapesCount == 0) {
		emptyArrayMessage();
		return;
	}
		
	
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << "(" << i + 1 << ") " << shapes[i]->getArea() << std::endl;
	}
}

void ShapeCollection::pers() const
{
	if (shapesCount == 0) {
		emptyArrayMessage();
		return;
	}

	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << "(" << i + 1 << ") " << shapes[i]->getPer() << std::endl;
	}
}

void ShapeCollection::print() const
{
	if (shapesCount == 0) {
		emptyArrayMessage();
		return;
	}

	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << i << ". ";
		shapes[i]->print();
	}
}

void ShapeCollection::pointIn(double x, double y) const
{
	if (shapesCount == 0)
	{
		emptyArrayMessage();
		return;
	}

	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x, y))
			shapes[i]->print();
	}
}

void ShapeCollection::saveFiguresToFile() const
{
	std::ofstream f(fileName.c_str(), std::ios::trunc);
	if (!f.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
		return;
	}

	try
	{
		f << "<?xml version=\"1.0\" standalone=\"no\"?>\n"
			<< "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
			<< "<svg xmlns=\"http://www.w3.org/2000/svg\">\n";
		for (size_t i = 0; i < shapesCount; i++)
		{
			f << "<";
			shapes[i]->writeToFile(f);
			f << "/>\n";
		}
		f << "</svg>";
		std::cout << "Successfully saved the changes to " << fileName << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	f.close();
}

void outOfRangeMessage(int i)
{
	std::cout << "There is no figure number " << i << "!" << std::endl;
}

void emptyArrayMessage()
{
	std::cout << "There are no figures!" << std::endl;
}


bool ShapeCollection::readFromFile()
{
	free();
	std::cout << "Enter file name/path: \n> ";
	std::cin >> fileName;

	std::ifstream f(fileName.c_str());

	if (!f.is_open())
	{
		std::cout << "Error while opening the file!\n";
		shapesCount = 0;
		shapes = nullptr;
		return false;
	}

	aString currWord;
	char buff[buffCapacity];
	char ch;

	f.getline(buff, capacity); ///skip the first 3 lines 
	f.getline(buff, capacity); 
	f.getline(buff, capacity);

	aString color;
	while (!f.eof())
	{
		ch = f.get();
		if (ch == ' ')
		{
			if (currWord == "<rect")
			{
				double x = ConvertStringToDouble(getFieldValue(f));
				double y = ConvertStringToDouble(getFieldValue(f));
				double width = ConvertStringToDouble(getFieldValue(f));
				double height = ConvertStringToDouble(getFieldValue(f));
				color = getFieldValue(f);
				addShape(new Rectangle(x, y, width, height, color));
				currWord = "";
				f.getline(buff, buffCapacity);
			}
			else if (currWord == "<circle")
			{
				double x = ConvertStringToDouble(getFieldValue(f));
				double y = ConvertStringToDouble(getFieldValue(f));
				double radius = ConvertStringToDouble(getFieldValue(f));
				color = getFieldValue(f);
				addShape(new Circle(x, y, radius, color));
				currWord = "";
				f.getline(buff, buffCapacity);
			}
			else if (currWord == "<line")
			{
				double x1 = ConvertStringToDouble(getFieldValue(f));
				double y1 = ConvertStringToDouble(getFieldValue(f));
				double x2 = ConvertStringToDouble(getFieldValue(f));
				double y2 = ConvertStringToDouble(getFieldValue(f));
				color = getFieldValue(f);
				addShape(new Line(x1, y1, x2, y2, color));
				currWord = "";
				f.getline(buff, buffCapacity);
			}

		}
		else
		{
			if (ch != ' ' && ch != '\n')
				currWord += ch;
		}
	}
	return true;
}

static const aString& getFieldValue(std::istream& s)
{
	aString result;
	char ch[2];
	ch[1] = '\0'; //because my += operator does not wwork with only chars
	ch[0] = s.get();
	while (ch[0] != '"')
		ch[0] = s.get();
	ch[0] = s.get();
	while (ch[0] != '"')
	{
		result += ch;
		ch[0] = s.get();
	}
	return result;
}

double ConvertStringToDouble(const aString& str)
{
	bool isNegative = false;
	int i = 0;
	if (str[0] == '-')
	{
		isNegative = true;
		i = 1;
	}
	aString temp;
	char ch[2];
	ch[0]= str[i];
	ch[1] = '\0';
	
	while (ch[0] !=',' && ch[0] != '.' && ch[0] != '\0') // for the Z number
	{
		ch[0] = str[i];
		temp += ch;
		i++;
	}

	double number = 0;
	int multBy10 = 1;
	for (int j = temp.getSize() - 2; j >= 0; j--)
	{
		if (temp[j] < 48 || temp[j] > 57)
		{
			return -1;
		}
		number += (temp[j] - 48) * multBy10;
		multBy10 *= 10;
	}

	double num2 = 0;
	multBy10 = 1;
	for (size_t j = str.getSize() - 1; j >= temp.getSize(); j--)
	{
		if (str[j] < 48 || str[j] > 57)
		{
			return -1;
		}
		num2 += (str[j] - 48) * multBy10;
		multBy10 *= 10;
	}
	
	number += num2 / multBy10;
	if (isNegative)
		number *= -1;
	return number;
}