#include <iostream>
#include "Derived.h"

Derived::Derived() {
	std::cout << "hello, world\n";
}

Derived::~Derived() {
	std::cout << "goodbye, world\n";
}

Base *createDerived() {
	return new Derived();
}
