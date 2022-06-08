#include "Account.h"

void Account::setPassword(const aString& pass)
{
	password = pass;
}

Account::Account(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date)
{
	setUsername(u);
	setPassword(p);
	setIban(iban);
	setId(id);
	setDateOfCreation(date);
}

void Account::printMainAccountInfo() const
{
	std::cout << "IBAN: " << iban << std::endl
		<< "Customer ID: " << id << std::endl
		<< "Balance: " << amount << std::endl;
}

Account::~Account()
{}

void Account::setUsername(const aString& u)
{
	username = u;
}
void Account::changePassword(const aString& oldPass, const aString& newPass)
{
	if (oldPass == password)
		setPassword(newPass);
}

void Account::setIban(const aString& iban)
{
	this->iban = iban;
}

void Account::setId(size_t id)
{
	this->id = id;
}

void Account::setAmount(double amount)
{
	this->amount = amount;
}

void Account::setDateOfCreation(const time_t& date)
{
	dateOfCreation = date;
}

void Account::deposit(double sum)
{
	amount += sum;
}

double Account::getBalance() const
{
	return amount;
}

const aString& Account::getUsername() const
{
	return username;
}

const aString& Account::getIban() const
{
	return iban;
}

const time_t& Account::getDateOfCreation() const
{
	return dateOfCreation;
}

bool Account::checkId(size_t s) const
{
	return s == id;
}

size_t Account::getID() const
{
	return id;
}

bool Account::checkPassword(const aString& pass) const
{
	return password == pass;
}