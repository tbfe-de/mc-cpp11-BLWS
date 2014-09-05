#include <boost/algorithm/string.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

int foo(int n) {
	return 100*(n / 1000) + (n % 10);
}

int main(int argc, const char *argv[])
{
	using namespace boost;
	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;
	std::vector<int> data;

	std::copy(
		in(std::cin), in(),
		std::back_inserter(data)
	);

	std::for_each(
		data.begin(), data.end(),
		// call function foo to change value:
		// _1 = bind(foo, _1)

		// alternatively as lambda expression:
		_1 = 100*(_1 / 1000) + (_1 % 10)
	);

	std::copy(
		data.begin(), data.end(),
		std::ostream_iterator<int>(std::cout, " ")
	);
	std::cout << std::endl;
}
