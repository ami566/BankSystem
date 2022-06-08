#include "Shape.h"
#include <iostream>
Shape::Shape(size_t pointsCount, const aString& color) : pointsCount(pointsCount), color(color)
{
	points = new point[pointsCount]; // [0,0], [0,0]....
}

void Shape::copyFrom(const Shape& other)
{
	points = new point[other.pointsCount];

	for (int i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;
}
void Shape::free()
{
	delete[] points;
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}
Shape& Shape::operator= (const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Shape::~Shape()
{
	free();
}

const Shape::point& Shape::getPointAtIndex(size_t index) const
{
	if (index >= pointsCount)
		throw std::exception("Invalid point index!");

	return  points[index];
}

void Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
		throw std::exception("Invalid point index!");

	points[pointIndex] = point(x, y);
}

void Shape::translate(double vertical, double horizontal)
{
	for (size_t i = 0; i < pointsCount; i++)
	{
		points[i].x += horizontal;
		points[i].y += vertical;
	}
}

bool Shape::isShapeWithinShape(const Shape* sh) const
{
	for (size_t i = 0; i < pointsCount; i++)
	{
		if (!sh->isPointIn(points[i].x, points[i].y))
			return false;
	}
	return true;
}
