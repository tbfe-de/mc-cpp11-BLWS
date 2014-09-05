#include <boost/algorithm/string.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>

int main(int argc, const char *argv[])
{
	using namespace boost;
	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;

	if (argc != 2) {
		std::cerr << "Usage: multiply factor" << std::endl;
		return EXIT_FAILURE;
	}

	int factor;
	try {
		factor= lexical_cast<int>(argv[1]);
	}
	catch (bad_lexical_cast &) {
		std::cerr << "multiply: factor is not a number" << std::endl;
		return EXIT_FAILURE;
	}

	std::for_each(
		in(std::cin), in(),
		std::cout << (factor * _1) << '\n'
	);
}
