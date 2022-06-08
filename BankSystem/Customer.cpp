#include "Customer.h"

Customer::Customer(size_t id, const aString& n, const aString& ad)
{
	setID(id);
	setName(n);
	setAddress(ad);
}

size_t Customer::getID() const
{
	return id;
}

const aString& Customer::getName() const
{
	return name;
}

const aString& Customer::getAddress() const
{
	return address;
}

void Customer::setID(size_t id)
{
	this->id = id;
}

void Customer::setName(const aString& n)
{
	name = n;
}

void Customer::setAddress(const aString& ad)
{
	address = ad;
}

void Customer::printInfo() const
{
	std::cout << id << ", " << name << ", " << address << std::endl;
}
