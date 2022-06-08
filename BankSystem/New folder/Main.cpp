#include "Main.h"
#include "NormalAccount.h"
#include "SavingsAccount.h"
#include "PrivilegeAccount.h"

int Bank::exportedLogs = 0;

void Main(Bank& b)
{
	aString input;
	while (true)
	{
		std::cout << "\n\nChoose your option (type it as a combination of all bullet points and/or characters) \n"
			<<"Example: for 'delete account' type '1bii' \n";
		displayMenu();
		std::cout << "\n\n> ";

		std::cin >> input;
		if (input == "1ai")
			addCust(b);
		else if (input == "1aii")
			deleteCust(b);
		else if (input == "1bi")
			addAcc(b);
		else if (input == "1bii")
			deleteAcc(b);
		else if (input == "2a")
			listAllCust(b);
		else if (input == "2b")
			listAllAccs(b);
		else if (input == "2c")
			listCustAccs(b);
		else if (input == "2d")
			listLog(b);
		else if (input == "3a")
			withdraw(b);
		else if (input == "3b")
			deposit(b);
		else if (input == "3c")
			transfer(b);
		else if (input == "4")
			bankInfo(b);
		else if (input == "5")
			return;
	}
}

void displayMenu()
{
	std::cout << "1. Edit\n"
		<< "\ta.Customer\n"
		<< "\t\ti.Add new customer\n"
		<< "\t\tii.Delete customer\n"
		<< "\tb.Account\n"
		<< "\t\ti.Add new account\n"
		<< "\t\tii.Delete account\n"
		<< "2. List\n"
		<< "\ta.List all customers\n"
		<< "\tb.List all accounts\n"
		<< "\tc.List customer account\n"
		<< "\td.List log\n"
		<< "3. Action\n"
		<< "\ta.Withdraw from account\n"
		<< "\tb.Deposit to account\n"
		<< "\tc.Transfer\n"
		<< "4. Display info for the bank\n"
		<< "5. Quit\n";
}

void bankInfo(Bank& b)
{
	b.display();
}

void addAcc(Bank& b)
{
	aString type, iban, username, pass ;
	size_t id;
	double amount;
	Account* acc;
	std::cout << "Enter all the needed information about the new account: \n"
		<< "> IBAN: ";
	std::cin >> iban;
	std::cout << "> ID: ";
	std::cin >> id;
	std::cout << "> Username: ";
	std::cin >> username;
	std::cout << "> Password: ";
	std::cin >> pass;
	std::cout << "> Amount: ";
	std::cin >> amount;
	std::cout << "> Type (normal, savings, privilege): ";
	std::cin >> type;

	double input;
	time_t t = time(0);
	if (type == "normal")
	{
		acc = new NormalAccount(username, pass, iban, id, t);
	}
	else if (type == "savings")
	{
		std::cout << "> Interest rate: ";
		std::cin >> input;
		acc = new SavingsAccount(username, pass, iban, id, t, input);
	}
	else if (type == "privilege")
	{
		std::cout << "> Overdraft: ";
		std::cin >> input;
		acc = new PrivilegeAccount(username, pass, iban, id, t, input);
	}
	else
	{
		std::cout << "Invalid account type!\n";
		return;
	}

	acc->setAmount(amount);
	b.addAccount(acc, type);
}

void addCust(Bank& b)
{
	aString name, address;
	size_t id;
	std::cout << "Type in the information about the new customer: \n"
		<< "> Name: ";
	std::cin >> name;
	
	std::cout << "> Address: ";
	std::cin.ignore();
	std::cin >> address;
	std::cout << "> ID: ";
	std::cin >> id;
	b.addCustomer(new Customer(id, name, address));
}

void deleteAcc(Bank& b)
{
	aString iban, username, pass;
	size_t id;
	std::cout << "Enter all the needed info about the account: \n"
		<< "> IBAN: ";
	std::cin >> iban;
	std::cout << "> ID: ";
	std::cin >> id;
	std::cout << "> Username: ";
	std::cin >> username;
	std::cout << "> Password: ";
	std::cin >> pass;
	b.deleteAccount(iban, username, pass, id);
}

void deleteCust(Bank& b)
{
	aString name;
	size_t id;
	std::cout << "Enter all the needed info about the customer: \n"
		<< "> Name: ";
	std::cin >> name;
	std::cout << "> ID: ";
	std::cin >> id;
	b.deleteCustomer(id, name);
}

void listAllAccs(Bank& b)
{
	b.listAccounts();
}

void listAllCust(Bank& b)
{
	b.listCustomers();
}

void listCustAccs(Bank& b)
{
	size_t input;
	std::cout << "Type in the ID of the customer:\n> ";
	std::cin >> input;
	b.listCustomerAccount(input);
}

void listLog(Bank& b)
{
	b.printLog();
}


void withdraw(Bank& b)
{
	aString iban, username, pass;
	size_t id;
	double amount;
	std::cout << "Enter all the needed info about the account: \n"
		<< "> IBAN: ";
	std::cin >> iban;
	std::cout << "> ID: ";
	std::cin >> id;
	std::cout << "> Username: ";
	std::cin >> username;
	std::cout << "> Password: ";
	std::cin >> pass;
	std::cout << "> Amount to withdraw: ";
	std::cin >> amount;
	if(b.withdraw(amount, iban, username, pass, id))
		std::cout<< "Transaction successfull!\n";
}

void deposit(Bank& b)
{
	aString iban, username, pass;
	size_t id;
	double amount;
	std::cout << "Enter all the needed info about the account: \n"
		<< "> IBAN: ";
	std::cin >> iban;
	std::cout << "> ID: ";
	std::cin >> id;
	std::cout << "> Username: ";
	std::cin >> username;
	std::cout << "> Password: ";
	std::cin >> pass;
	std::cout << "> Amount to deposit: ";
	std::cin >> amount;
	b.deposit(amount, iban, username, pass, id);
}

void transfer(Bank& b)
{
	aString iban1, username, pass, iban2;
	size_t id1, id2;
	double amount;
	std::cout << "Enter all the needed info about the account that would be sending the money: \n"
		<< "> IBAN: ";
	std::cin >> iban1;
	std::cout << "> ID: ";
	std::cin >> id1;
	std::cout << "> Username: ";
	std::cin >> username;
	std::cout << "> Password: ";
	std::cin >> pass;
	std::cout << "> Amount to transfer: ";
	std::cin >> amount;
	std::cout << "Enter all the needed info about the account that will receive the money: \n"
		<< "> IBAN: ";
	std::cin >> iban2;
	std::cout << "> ID: ";
	std::cin >> id2;

	b.transfer(id1, iban1, username, pass, id2, iban2, amount);
}
