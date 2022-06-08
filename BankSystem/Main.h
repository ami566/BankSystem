#pragma once
#include "Bank.h"

void Main(Bank& b);
void displayMenu();
void bankInfo(Bank& b);

void addAcc(Bank& b);
void addCust(Bank& b);
void deleteAcc(Bank& b);
void deleteCust(Bank& b);

void listAllAccs(Bank& b);
void listAllCust(Bank& b);
void listCustAccs(Bank& b);
void listLog(Bank& b);

void withdraw(Bank& b);
void deposit(Bank& b);
void transfer(Bank& b);

