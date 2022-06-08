#include "Controller.h"

void Start(ShapeCollection* sc)
{
	bool figuresLoaded;
	aString input;
	

	while (true) 
	{
		std::cout << "Choose an option: \n"
			<< "1. Open\n"
			<< "2. Exit\n\n> ";
		std::cin >> input;
		if (input == "2")
			break;

		if (input == "1")
		{
			figuresLoaded = sc->readFromFile();
			if (!figuresLoaded)
				continue;

			Main(sc);
			break;
		}
		
	}
	std::cout << "Exit \n";
}

void Main(ShapeCollection* sc)
{
	aString input;
	
	while (!(input == "10"))
	{
		DisplayMenu();
		std::cout << "> ";
		std::cin >> input;

		if (input == "1")
		{
			Print(sc);
		}
		else if (input == "2")
		{
			Create(sc);
		}
		else if (input == "3")
		{
			Erase(sc);
		}
		else if (input == "4")
		{
			Translate(sc);
		}
		else if (input == "5")
		{
			Within(sc);
		}
		else if (input == "6")
		{
			PointIn(sc);
		}
		else if (input == "7")
		{
			Areas(sc);
		}
		else if (input == "8")
		{
			Pers(sc);
		}
		else if (input == "9")
		{
			Save(sc);
		}
	}
}

void DisplayMenu()
{
	std::cout << "Choose an option: \n"
		<< "1. Print\n"
		<< "2. Create\n"
		<< "3. Erase\n"
		<< "4. Translate\n"
		<< "5. Within\n"
		<< "6. PointIn\n"
		<< "7. Areas\n"
		<< "8. Pers\n"
		<< "9. Save to file\n"
		<< "10. Quit\n";
}

void Print(ShapeCollection* sc)
{
	sc->print();
}

void Create(ShapeCollection* sc)
{
	aString input;
	std::cout << "Enter the type of the shape (rectangle, circle, line): \n>";
	std::cout << "> ";
	std::cin >> input;
	// I am aware these should have been each one in their respecitive class, i just did't have the time to change it
	if (input == "rectangle")
	{
		double x, y, width, height, color;
		std::cout << "Enter x and y: \n> ";
		std::cin >> x;
		std::cout << "\n> ";
		std::cin >> y;
		std::cout << "Enter width and height: \n> ";
		std::cin >> width;
		std::cout << "\n> ";
		std::cin >> height;
		std::cout << "Enter color: \n> ";
		std::cin >> color;
		sc->addShape(new Rectangle(x, y, width, height, color));
	}
	else if (input == "circle")
	{
		double x, y, radius, color;
		std::cout << "Enter x and y: \n> ";
		std::cin >> x;
		std::cout << "\n> ";
		std::cin >> y;
		std::cout << "Enter radius: \n> ";
		std::cin >> radius;
		std::cout << "Enter color: \n> ";
		std::cin >> color;
		sc->addShape(new Circle(x, y, radius, color));
	}
	else if (input == "line")
	{
		double x, y, x1, y1, color;
		std::cout << "Enter x and y coordinates for the first point: \n> ";
		std::cin >> x;
		std::cout << "\n> ";
		std::cin >> y;
		std::cout << "Enter x and y coordinates for the second point: \n> ";
		std::cin >> x1;
		std::cout << "\n> ";
		std::cin >> y1;
		std::cout << "Enter color: \n> ";
		std::cin >> color;
		sc->addShape(new Line(x, y, x1, y1, color));
	}
	else
		std::cout << "There is no such shape!";

}

void Erase(ShapeCollection* sc)
{
	std::cout << "Type the index of the shape you want to delete: ";
	size_t index;
	std::cin >> index;

	sc->erase(index);
}

void Translate(ShapeCollection* sc)
{
	aString input;
	double x, y;
	std::cout << "Enter vertical and horizontal: \n> ";
	std::cin >> x;
	std::cout << "\n> ";
	std::cin >> y;
	std::cout << "Enter index of figure to translate (type 'all' for all): \n> ";
	std::cin >> input;
	if (input == "all")
		sc->translate(y, x, -1);
	else {
		try
		{
			sc->translate(y, x, ConvertStringToDouble(input));
		}
		catch (const std::exception&)
		{
			std::cout << "No such figure ecxists!" << std::endl;
		}
	}
		
}

void Within(ShapeCollection* sc)
{
	aString input;
	std::cout << "Enter the type of the shape (rectangle, circle): \n>";
	std::cout << "> ";
	std::cin >> input;

	if (input == "rectangle")
	{
		double x, y, width, height, color;
		std::cout << "Enter x and y: \n> ";
		std::cin >> x;
		std::cout << "\n> ";
		std::cin >> y;
		std::cout << "Enter width and height: \n> ";
		std::cin >> width;
		std::cout << "\n> ";
		std::cin >> height;
		std::cout << "Enter color: \n> ";
		std::cin >> color;
		sc->within(new Rectangle(x, y, width, height, color));
	}
	else if (input == "circle")
	{
		double x, y, radius, color;
		std::cout << "Enter x and y: \n> ";
		std::cin >> x;
		std::cout << "\n> ";
		std::cin >> y;
		std::cout << "Enter radius: \n> ";
		std::cin >> radius;
		std::cout << "Enter color: \n> ";
		std::cin >> color;
		sc->within(new Circle(x, y, radius, color));
	}
}

void PointIn(ShapeCollection* sc)
{
	double x, y;
	std::cout << "Type the coordinates of the point: \n> ";
	std::cin >> x;
	std::cout << "> ";
	std::cin >> y;
	sc->pointIn(x, y);
}

void Areas(ShapeCollection* sc)
{
	sc->areas();
}

void Pers(ShapeCollection* sc)
{
	sc->pers();
}

void Save(ShapeCollection* sc)
{
	sc->saveFiguresToFile();
}