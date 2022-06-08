#include "Shape.h"

class Rectangle : public Shape
{
	double width;
	double height;

public:
	//Rectangle(int x1, int y1, int x3, int y3);
	Rectangle(double x, double y, double width, double height, const aString& color);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void writeToFile(std::ofstream& s) const override;
	void print() const override;

};