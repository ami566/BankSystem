#pragma once
#include <iostream>
#include <fstream>
#include "aString.h"
class Shape   // Abstract class - no instances of Shape are allowed!
{
protected:
	struct point
	{
		point() :x(0), y(0) {}
		point(double x, double y) :x(x), y(y) {}
		double x;
		double y;
		double getDist(const point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
		void printPoint() const
		{
			std::cout << x << " " << y;
		}
	};
	aString color;
	const point& getPointAtIndex(size_t index) const;

private:
	point* points;
	size_t pointsCount;
	void copyFrom(const Shape& other);
	void free();


public:
	Shape(size_t pointsCount, const aString& color);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	void setPoint(size_t pointIndex, double x, double y);

	virtual void print() const = 0;
	void translate(double vertical, double horizontal);
	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual bool isPointIn(double x, double y) const = 0;
	bool isShapeWithinShape(const Shape* sh) const;
	virtual Shape* clone() const = 0;
	virtual void writeToFile(std::ofstream& s) const = 0;
	//virtual void readFromFile(std::ifstream& s) const = 0;

};
