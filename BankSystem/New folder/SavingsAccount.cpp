#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date, double rate) : Account(u, p, iban, id, date)
{
	setInterestRate(rate);
}

void SavingsAccount::setInterestRate(double rate)
{
	interestRate = rate;
}

double SavingsAccount::getInterestRate() const
{
	return interestRate;
}

bool SavingsAccount::withdraw(double sum)
{
	std::cout << "You cannot withdraw from a savings acoount!\n";
	return false;
}

void SavingsAccount::display() const
{
	std::cout << "Account type: Savings account" << std::endl;
	printMainAccountInfo();
	std::cout << "Interest rate: " << interestRate << std::endl;
}

Account* SavingsAccount::clone() const
{
	return new SavingsAccount(*this);
}
