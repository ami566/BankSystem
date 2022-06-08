#include "NormalAccount.h"
#include <iostream>

NormalAccount::NormalAccount(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date) : Account(u, p, iban, id, date)
{
}

bool NormalAccount::withdraw(double sum)
{
	if (sum > amount)
	{
		std::cout << "Not enough money to withdraw!\n";
		return false;
	}
		

	amount -= sum;
	return true;
}

void NormalAccount::display() const
{
	std::cout << "Account type: Normal account" << std::endl;
	printMainAccountInfo();
}

Account* NormalAccount::clone() const
{
	return new NormalAccount(*this);
}
