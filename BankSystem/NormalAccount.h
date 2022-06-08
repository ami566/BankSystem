#pragma once
#include "Account.h"
class NormalAccount :
    public Account
{
public:
    NormalAccount() = default;
    NormalAccount(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date);
    bool withdraw(double sum) override;
    void display() const override;

    Account* clone() const override;
};

