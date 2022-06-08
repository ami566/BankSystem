#include "Bank.h"
#include <fstream>

#pragma warning (disable: 4996)


int Bank::customerExistsAt(size_t id) const
{
	for (size_t i = 0; i < customers.Size(); i++)
	{
		if (customers[i].getID() == id)
			return i;
	}
	return -1;
}

int Bank::getAccountIndexFromIban(const aString& iban) const
{
	for (size_t i = 0; i < accounts.Size(); i++)
	{
		if (accounts[i]->getIban() == iban)
			return i;
	}

	return -1;
}

Bank::Bank(const aString& name, const aString& address)
{
	setName(name);
	setAddress(address);
}

void Bank::setName(const aString& n)
{
	name = n;
}

void Bank::setAddress(const aString& a)
{
	address = a;
}

const aString& Bank::getName() const
{
	return name;
}

const aString& Bank::getAddress() const
{
	return address;
}

void Bank::addCustomer(const Customer* c)
{
	if (customerExistsAt(c->getID()) != -1)
	{
		std::cout << "Customer with ID: " << c->getID() << " already exists!\n";
		return;
	}

	customers.push_back(c);
	log.push_back(new aString("Added new customer with ID : " + convertIntToString(c->getID()) + ".\n"));
	std::cout << "Customer added successfully!\n";
}

void Bank::deleteCustomer(size_t id, const aString& name)
{
	int index = customerExistsAt(id);
	if (index == -1)
	{
		std::cout << "Customer does not exist!\n";
		return;
	}

	if(!(customers[index].getName()==name))
	{
		std::cout << "ID and name do not match!\n";
		return;
	}

	size_t count = 0;
	size_t accountsSize = accounts.Size();

	int* indexes = new int[accountsSize];
	for (size_t i = 0; i < accountsSize; i++)
	{
		if (accounts[i]->checkId(id))
			indexes[count++] = i;
	}

	for (size_t i = 0; i < count - 1; i++) // s ili bez -1
	{
		accounts.deleteAt(indexes[i]);
	}

	customers.deleteAt(index);
	delete[] indexes;
	aString message = "Deleted customer with ID: " + convertIntToString(id) + ".\n";
	log.push_back(new aString(message));
	std::cout << message;
}

void Bank::addAccount(const Account* acc, const aString& type)
{
	if (getAccountIndexFromIban(acc->getIban()) != -1)
	{
		std::cout << "Account with IBAN: " << acc->getIban() << " already exists!\n";
		return;
	}
	accounts.push_back(acc); // it uses clone() to add account

	if (customerExistsAt(acc->getID()) == -1)
	{
		std::cout << "Customer does not exist!\n";
		return;
	}

	log.push_back(new aString("Added new " + type + " account with IBAN : " + acc->getIban() + " to customer with ID : " + convertIntToString(acc->getID()) + ".\n"));
	std::cout << "Account added successfully!\n";
}

void Bank::deleteAccount(const aString& iban, const aString& username, const aString& password, size_t id)
{
	int index = getAccountIndexFromIban(iban);

	if (index == -1)
	{
		std::cout << "Account does not exist!\n";
		return;
	}

	if (confirmAccountInfo(accounts[index], username, password, id))
	{
		std::cout << "Invalid username, password or ID!\n";
		return;
	}

	accounts.deleteAt(index);
	log.push_back(new aString("Deleted account with IBAN: " + iban + ".\n"));
}

bool Bank::confirmAccountInfo(const Account* acc, const aString& username, const aString& password, size_t id)
{
	return !acc->checkPassword(password) || !(username == acc->getUsername()) || id != acc->getID();
}
void Bank::listCustomers() const
{
	size_t size = customers.Size();
	if (customers.isEmpty())
	{
		std::cout << "There are no customers yet!\n";
		return;
	}
	for (size_t i = 0; i < size; i++)
		customers[i].printInfo();
}

void Bank::listAccounts() const
{
	size_t size = accounts.Size();
	if (accounts.isEmpty()) 
	{
		std::cout << "There are no registered accounts yet!\n";
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		accounts[i]->display();
		std::cout << std::endl;
	}
		
}

void Bank::listCustomerAccount(size_t id) const
{
	if (customerExistsAt(id) == -1)
	{
		std::cout << "There is no customer with id: " << id << std::endl;
		return;
	}
	bool b = false;
	for (size_t i = 0; i < accounts.Size(); i++)
	{
		if (accounts[i]->checkId(id)) 
		{
			accounts[i]->display();
			std::cout << std::endl;
			b = true;
		}	
	}
	
	if (!b)
		std::cout << "This customer has not registered any accounts yet!\n";
}

void Bank::exportLog() const
{
	aString logName = "log_";
	std::time_t t = std::time(0);
	logName += convertIntToString(exportedLogs);
	logName.concat(".txt");
	std::ofstream f(logName.c_str());

	if (!f.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
		return;
	}

	try
	{
		size_t size = log.Size();
		f << logName << "\nLog exported on: " << ctime(&t) << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			f << i + 1 << ". " << log[i];
		}
		f << "Transactions count: " << size << std::endl;
		exportedLogs++;
	}
	catch (const std::exception&)
	{
		std::cout << "Error while exporting the log!" << std::endl;
		return;
	}
	f.close();
}

void Bank::transfer(size_t id1, const aString& iban1, const aString& username, const aString& pass, size_t id2, const aString& iban2, double amount)
{
	if (customerExistsAt(id1) == -1)
	{
		std::cout << "Transfer failed! Customer with id: "<< id1 <<"does not exist!" << std::endl;
		return;
	}
	if (customerExistsAt(id2) == -1)
	{
		std::cout << "Transfer failed! Customer with id: " << id2 << "does not exist!" << std::endl;
		return;
	}

	int indexOfAcc1 = getAccountIndexFromIban(iban1);
	int indexOfAcc2 = getAccountIndexFromIban(iban2);

	if (indexOfAcc1 == -1 || indexOfAcc2 == -1)
	{
		std::cout << "Transfer failed! Account does not exist!" << std::endl;
		return;
	}

	if (accounts[indexOfAcc1]->withdraw(amount))
	{
		accounts[indexOfAcc1]->deposit(amount);
		std::cout << "Transfer successfull!" << std::endl;
		log.push_back(new aString("Tranfered money from IBAN " + iban1 + " with identificator " + convertIntToString(id1) + " to  IBAN " + iban2 + " with identificator " + convertIntToString(id2) + ".\n"));
		return;
	}

	if (confirmAccountInfo(accounts[indexOfAcc1], username, pass, id1))
	{
		std::cout << "Tranfer failed! Invalid username, password or ID!\n";
		return;
	}

	std::cout << "Transfer failed!\n";
	return;
}

void Bank::display() const
{
	std::cout << "Bank: " << name << std::endl
		<< "Address: " << address << std::endl
		<< "Customers count: " << customers.Size() << std::endl
		<< "Accounts count: " << accounts.Size() << std::endl;
}

void Bank::printLog() const
{
	if (log.isEmpty())
	{
		std::cout << "There are no transactions made yet!\n";
		return;
	}

	for (size_t i = 0; i < log.Size(); i++)
	{
		std::cout << i + 1 << ". " << log[i];
	}

	exportLog();
}

bool Bank::withdraw(double amount, const aString& iban, const aString& username, const aString& password, size_t id)
{
	int index = getAccountIndexFromIban(iban);

	if (index == -1)
	{
		std::cout << "Account does not exist!\n";
		return false;
	}

	if (confirmAccountInfo(accounts[index], username, password, id))
	{
		std::cout << "Invalid username, password or ID!\n";
		return false;
	}

	//need function to convert double to string for the amount but for the log I wil use the one that converts it to int
	log.push_back(new aString("Customer with ID: " + convertIntToString(accounts[index]->getID()) + " withdrew " + convertIntToString(amount) + " from account with IBAN : " + accounts[index]->getIban() + ".\n"));
	return accounts[index]->withdraw(amount);
}

void Bank::deposit(double amount, const aString& iban, const aString& username, const aString& password, size_t id)
{
	int index = getAccountIndexFromIban(iban);

	if (index == -1)
	{
		std::cout << "Account does not exist!\n";
		return;
	}

	if (confirmAccountInfo(accounts[index], username, password, id))
	{
		std::cout << "Invalid username, password or ID!\n";
		return;
	}

	std::cout << "Transaction succeeded! \n";
	accounts[index]->deposit(amount);
}


aString convertIntToString(int a)
{
	int copy = a;
	int count = 0;
	while (copy > 0)
	{
		count++;
		copy /= 10;
	}

	char* str = new char[count + 1];
	str[count] = '\0';

	for (int i = count - 1; i >= 0; i--)
	{
		int b = a % 10;
		str[i] = b + 48;
		a /= 10;
	}

	aString string(str);
	delete[] str;

	return string;
}