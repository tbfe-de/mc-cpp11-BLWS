class Base; // forward declaration

extern Base *createDerived();

#include <iostream>

int main() {
	auto p = createDerived();
	std::cout << "... working ...\n";
	delete p;
}
