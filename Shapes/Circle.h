#pragma once
#include "Shape.h"
#include "Shape.h"

class Circle : public Shape
{
	double radius;

public:
	Circle(double x, double y, double radius, const aString& c);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void print() const override;
	void writeToFile(std::ofstream& s) const override;
};

