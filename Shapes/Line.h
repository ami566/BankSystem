#pragma once
#include "Shape.h"
class Line :  public Shape
{
public:
	Line(double x1, double y1, double x2, double y2, const aString& color);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void writeToFile(std::ofstream& s) const override;
	void print() const override;

};

