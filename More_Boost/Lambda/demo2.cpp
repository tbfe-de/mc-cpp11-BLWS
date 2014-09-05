#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>

#include <boost/function.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/ref.hpp>

#include <vector>

struct X {
	int a;
	double b;
	X(const int a_, const double b_)
		: a(a_), b(b_)
	{}
};

int main() {
	std::vector<X> v;
	v.push_back(X(3, 17.5));
	v.push_back(X(7, -.35));
	v.push_back(X(0, 1.0));

	using boost::lambda::bind;
	using boost::lambda::constant;
	using boost::lambda::_1;
	using boost::lambda::_2;

	boost::function<void (const X&)> Xprinter = (
		std::cout
			<< constant("a=") << bind(&X::a, _1) << constant(' ')
			<< constant("b=") << bind(&X::b, _1) << constant('\n')
	);

	std::cout << "Sorted by a:" << std::endl;
	std::sort(v.begin(), v.end(), bind(&X::a, _1) < bind(&X::a, _2));
	std::for_each(v.begin(), v.end(), Xprinter); 

	std::cout << "Sorted by b:" << std::endl;
	std::sort(v.begin(), v.end(), bind(&X::b, _1) < bind(&X::b, _2));
	std::for_each(v.begin(), v.end(), Xprinter); 
}
