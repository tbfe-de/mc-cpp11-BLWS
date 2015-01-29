#include "Base.h"

extern Base* createDerived();

#include <iostream>
//#include <boost/checked_delete.hpp>

int main() {
	auto p = createDerived();
	std::cout << "... working ...\n";
 	delete p;
	//boost::checked_delete(p);
}
