#pragma once
#include "aString.h"
#include <ctime>

class Account
{
	aString username;
	aString password;
	time_t dateOfCreation;
	void setPassword(const aString& pass);

protected:
	aString iban;
	size_t id;
	double amount = 0;
	
	void printMainAccountInfo() const;
	
public:
	Account() = default;
	Account(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date);
	virtual ~Account();

	void setUsername(const aString& u);
	void changePassword(const aString& oldPass, const aString& newPass);
	bool checkPassword(const aString& pass) const;
	void setIban(const aString& iban);
	void setId(size_t id);
	void setAmount(double amount);
	void setDateOfCreation(const time_t& date);

	void deposit(double sum);
	virtual bool withdraw(double sum) = 0;
	virtual void display() const = 0;
	double getBalance() const;
	virtual Account* clone() const = 0;

	bool checkId(size_t s) const;
	const aString& getUsername() const;
	size_t getID() const;
	const aString& getIban() const;
	const time_t& getDateOfCreation() const;
};

