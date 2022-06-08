#include "Circle.h"
const double PI = 3.1415;
Circle::Circle(double x, double y, double radius, const aString& c) : Shape(1, c), radius(radius)
{
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}
double Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}
Shape* Circle::clone() const
{
	Shape* copy = new Circle(*this);
	return copy;
}

void Circle::print() const
{
	std::cout << "circle ";
	getPointAtIndex(0).printPoint();
	std::cout << " " << radius << " " << color << std::endl;
}

void Circle::writeToFile(std::ofstream& s) const
{
	s << "circle cx=\"" << getPointAtIndex(0).x << "\" cy=\"" << getPointAtIndex(0).y << "\" "
		<< "r=\"" << radius << "\" fill = \"" << color << "\"";
}
