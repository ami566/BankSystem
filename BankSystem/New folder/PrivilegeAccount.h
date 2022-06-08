#pragma once
#include "Account.h"
class PrivilegeAccount :
    public Account
{
    double overdraft;

public:
    PrivilegeAccount() = default;
    PrivilegeAccount(const aString& u, const aString& p, const aString& iban, size_t id, const time_t& date, double overdraft);

    void setOverdraft(double sum);
    double getOverdraft() const;

    bool withdraw(double sum) override;
    void display() const override;
    Account* clone() const override;
};

