#include <iostream>
#include "Main.h"
int main() {
 
	aString name, address;
	std::cout << "> Enter bank name: ";
	std::cin >> name;
	std::cout << "> Enter address of the bank: ";
	std::cin >> address;

	Bank b(name, address);
	Main(b);
}