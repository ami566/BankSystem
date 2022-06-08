#pragma once
#include "Customer.h"

class Bank
{
	aString name;
	aString address;
	Vector<Customer> customers;
	Vector<Account*> accounts;
	static int exportedLogs;
	Vector<aString> log;

	int customerExistsAt(size_t id) const;
	int getAccountIndexFromIban(const aString& iban) const;
	bool confirmAccountInfo(const Account* acc, const aString& username, const aString& password, size_t id);

public:
	Bank() = default;
	Bank(const aString& name, const aString& address);

	void setName(const aString& n);
	void setAddress(const aString& a);
	const aString& getName() const;
	const aString& getAddress() const;

	void addCustomer(const Customer* c);
	void deleteCustomer(size_t id, const aString& name);
	void addAccount(const Account* acc, const aString& type);
	void deleteAccount(const aString& iban, const aString& username, const aString& password, size_t i);
	void listCustomers() const;
	void listAccounts() const;
	void listCustomerAccount(size_t id) const;
	void exportLog() const;
	void transfer(size_t id1, const aString& iban1, const aString& username, const aString& pass, size_t id2, const aString& iban2, double amount);
	void display() const;
	void printLog() const;
	bool withdraw(double amount, const aString& iban, const aString& username, const aString& password, size_t id);
	void deposit(double amount, const aString& iban, const aString& username, const aString& password, size_t id);
};

aString convertIntToString(int a);
