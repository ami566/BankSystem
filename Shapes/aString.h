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
	aString(int b);

	aString(const aString&);
	aString& operator=(const aString& other);

	~aString();
	bool operator==(const aString& other) const;
	aString& operator+=(const aString& other);
	char operator[](size_t i) const;
	size_t getSize() const;
	void concat(const aString& other);

	const char* c_str() const;

	friend std::ostream& operator<<(std::ostream& os, const aString& w);
	friend std::istream& operator>>(std::istream& is, aString& w);
};

