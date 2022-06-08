#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void resize();

	aString fileName;

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	void addShape(const Shape* shape);
	void erase(size_t i);
	void translate(double vertical, double horizontal, int i = -1);
	void within(const Shape* s) const;
	void areas() const;
	void pers() const;
	void print() const;
	void pointIn(double x, double y) const;

	bool readFromFile();
	void saveFiguresToFile() const;
};

void outOfRangeMessage(int i);
void emptyArrayMessage();
static const aString& getFieldValue(std::istream& is);
double ConvertStringToDouble(const aString& str);