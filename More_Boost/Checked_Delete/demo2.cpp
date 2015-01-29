class Base; // forward declaration

extern Base *createDerived();

#include <iostream>
#include <boost/checked_delete.hpp>

int main() {
	auto p = createDerived();
	std::cout << "... working ...\n";
 	boost::checked_delete(p);
}
