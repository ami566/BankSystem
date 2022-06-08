#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2, const aString& color): Shape(2, color)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
}

double Line::getArea() const
{
	return 1; // ???
}
double Line::getPer() const //??
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	return p0.getDist(p1);
}

bool Line::isPointIn(double px, double py) const
{ 
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	// with 0 coordinates it won;t work
	return py == ((p1.x - p0.y) / (p1.x - p0.x)) * px + (p0.y * p1.x - p0.x * p1.y) / (p1.x - p0.x);
}
Shape* Line::clone() const
{
	Shape* copy = new Line(*this);
	return copy;
}

void Line::writeToFile(std::ofstream& s) const
{
	s << "line x1=\"" << getPointAtIndex(0).x << "\" y1=\"" << getPointAtIndex(0).y << "\" "
	 << "x2=\"" << getPointAtIndex(1).x << "\" y2=\"" << getPointAtIndex(1).y << "\" "
		<< "\" stroke=\"" << color << "\"";

}

void Line::print() const
{
	std::cout << "line ";
	getPointAtIndex(0).printPoint();
	getPointAtIndex(1).printPoint();
	std::cout << " " << color << std::endl;
}