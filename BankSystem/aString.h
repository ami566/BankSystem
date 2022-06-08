#pragma once
#include <iostream>
class aString
{
	char* str;
	size_t size;

	void copyFrom(const aString& other);
	void free();
public:
	aString();
	aString(const char*);

	aString(const aString&);
	aString& operator=(const aString& other);

	~aString();
	bool operator==(const aString& other) const;
	aString& operator+=(const aString& other);
	
	char operator[](size_t i) const;
	size_t getSize() const;
	void concat(const aString& other);
	double convertToDouble() const;
	const char* c_str() const;

	friend aString operator+(const aString& lhs, const aString& rhs);
	friend std::ostream& operator<<(std::ostream& os, const aString& w);
	friend std::istream& operator>>(std::istream& is, aString& w);
};

