#include "aString.h"
#include <cstring>
#include <iomanip>

#pragma warning(disable : 4996)

void aString::copyFrom(const aString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	size = other.size;
}
void aString::free()
{
	delete[] str;
}

aString::aString()
{
	str = new char[1];
	str[0] = '\0';
	size = 0;
}

aString::aString(const char* data)
{
	size = strlen(data);
	str = new char[size + 1];
	strcpy(str, data);
}

aString::aString(int b)
{
	str = new char[1];
	str[0] = '\0';
	str += b;
	size = strlen(str);
}

aString::aString(const aString& other)
{
	copyFrom(other);
}
aString& aString::operator=(const aString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

aString::~aString()
{
	free();
}

size_t aString::getSize() const
{
	return size;
}

bool aString::operator==(const aString& other) const
{
	return strcmp(str, other.str) == 0;
}

aString& aString::operator+=(const aString& other)
{
	 concat(other);
	 return *this;
}

char aString::operator[](size_t i) const
{
	if (i >= size)
		return ' ';
	return str[i];
}

void aString::concat(const aString& other)
{
	char* temp = new char[getSize() + other.getSize() + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	delete[] str;
	str = temp;
	size = size + other.getSize();
}

const char* aString::c_str() const
{
	return str;
}

std::ostream& operator<<(std::ostream& os, const aString& w)
{
	os << w.str;
	return os;
}

std::istream& operator>>(std::istream& stream, aString& w)
{
	delete[] w.str;
	char buff[1024];
	stream >> std::setw(1024) >> buff;

	w.size = strlen(buff);
	w.str = new char[w.size + 1];
	strcpy(w.str, buff);

	return stream;
}