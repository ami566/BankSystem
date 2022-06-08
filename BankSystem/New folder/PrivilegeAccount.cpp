#include "PrivilegeAccount.h"

PrivilegeAccount::PrivilegeAccount(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date, double overdraft) : Account(u, p, iban, id, date)
{
	setOverdraft(overdraft);
}

void PrivilegeAccount::setOverdraft(double sum)
{
	overdraft = sum;
}

double PrivilegeAccount::getOverdraft() const
{
	return overdraft;
}

bool PrivilegeAccount::withdraw(double sum)
{
	if (amount + overdraft < sum)
	{
		std::cout << "Not enough money to withdraw!\n";
		return false;
	}
		

	amount -= sum;
	return true;
}

void PrivilegeAccount::display() const
{
	std::cout << "AccountType: Privilege account" << std::endl;
	printMainAccountInfo();
	std::cout << "Allowed overdraft: " << overdraft << std::endl;
}

Account* PrivilegeAccount::clone() const
{
	return new PrivilegeAccount(*this);
}
