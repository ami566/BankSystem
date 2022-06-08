#include"Rectangle.h"

Rectangle::Rectangle(double x, double y, double width, double height, const aString& color) : Shape(4, color)
{
	setPoint(0, x, y);
	setPoint(1, x + width, y);
	setPoint(2, x + width, y + height);
	setPoint(3, x, y + height);
}

double Rectangle::getArea() const
{
	return width * height;
}
double Rectangle::getPer() const
{
	return 2 * (width + height);
}

bool Rectangle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).x &&
		p.y <= getPointAtIndex(0).y && p.y >= getPointAtIndex(2).y;
}
Shape* Rectangle::clone() const
{
	Shape* copy = new Rectangle(*this);
	return copy;
}

void Rectangle::writeToFile(std::ofstream& s) const
{
	s << "rect x=\"" << getPointAtIndex(0).x << "\" y=\"" << getPointAtIndex(0).y << "\" "
		<< "width=\"" << width << "\" height=\"" << height << "\" fill=\"" << color << "\"";
}

void Rectangle::print() const
{
	std::cout << "rectangle ";
	getPointAtIndex(0).printPoint();
	std::cout << " " << width << " " << height << " " << color << std::endl;
}
