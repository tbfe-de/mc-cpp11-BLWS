//============================================================================
// Name        : donnerstag-x1.cpp
// Author      : mw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

struct MyClass {
	int key;
	double value;
    MyClass(int k, double d = 0.0) : key(k), value(d) {}
};

struct MyClass_less {
	bool operator()(const MyClass &lhs, const MyClass &rhs) const {
		return (lhs.key > rhs.key); }
};

using my_map = boost::bimap<
		boost::bimaps::set_of<std::string>,
		boost::bimaps::multiset_of<MyClass, MyClass_less>
>;

int main() {
	my_map m;

	m.insert(my_map::value_type("second", MyClass(1, 5.7)));
	m.insert(my_map::value_type("other", MyClass(2, 1.1)));
	m.insert(my_map::value_type("first", MyClass(1, 1.1)));
	m.insert(my_map::value_type("third", MyClass(100, 1.3)));

	for (const auto& e : m.left)
		std::cout << e.first << " -> "
				  << e.second.key << ", " << e.second.value << std::endl;
	for (const auto& e : m.right)
		std::cout << e.first.key << ", " << e.first.value << " -> "
				  << e.second << std::endl;

	auto f = m.left.find("second");
	std::cout << f->first << " -> " << f->second.key << ", "
			                    << f->second.value << std::endl;

	auto f2 = m.right.find(MyClass(100));
	std::cout << f2->first.key << ", " << f2->first.value << " -> "
			                    << f2->second << std::endl;

	auto f3 = m.right.equal_range(MyClass(1));
	std::cout << "-----\n";
#if 0
	std::for_each(f3.first, f3.second,
				  [](const my_map::right_map::value_type &e) {
						std::cout << e.get_right().key << ", " << e.get_right().value
								  << " -> " << e.get_left() << std::endl;
				  });
#else
	for (auto it = f3.first; it != f3.second; ++it)
		std::cout << it->get_right().key << ", " << it->get_right().value
				  << " -> " << it->get_left() << std::endl;

#endif
}
