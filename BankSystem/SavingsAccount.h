#pragma once
#include "Account.h"
class SavingsAccount :
    public Account
{
    double interestRate;
public:
    SavingsAccount() = default;
    SavingsAccount(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date, double rate);
    void setInterestRate(double rate);
    double getInterestRate() const;

    bool withdraw(double sum) override;
    void display() const override;
    Account* clone() const override;
};

