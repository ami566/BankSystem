#pragma once
#include "aString.h"
#include "Account.h"
#include "Vector.hpp"

class Customer
{
	size_t id;
	aString name;
	aString address;

public:
	Customer() = default;
	Customer(size_t id, const aString& n, const aString& ad);
	
	size_t getID() const;
	const aString& getName() const;
	const aString& getAddress() const;

	void setID(size_t id);
	void setName(const aString& n);
	void setAddress(const aString& ad);

	void printInfo() const;
};

