#include <iostream>
#include <sstream>
#include <string>

void sumlines(std::istream &in, std::ostream &out) {
	std::string line;
	while (std::getline(in, line)) {
		int sum = 0;
		std::istringstream iss(line);
		int ival;
		while (iss >> ival)
			sum += ival;
		out << sum << '\n';
	}
}

#define TDD
#ifndef TDD
int main() {
	sumlines(std::cin, std::cout);
}
#else
#include <cassert>
int main() {
	using namespace std;
	cout << "Note: no news is good news :-)" << endl;

	{ // Typical Example	     //	INPUT SUPPLIED
				     // --------------------
		istringstream si(	"3 4 5"		"\n"
		 			"7 8"		"\n"
					"9 10 11 12"	"\n"
					"17"		"\n");
		ostringstream so;    // OUTPUT EXPECTED	
		sumlines(si, so);    // --------------------
		assert(so.str() ==	"12"		"\n"
					"15"		"\n"
					"42"		"\n"
					"17"		"\n");
	}
	{ // Empty Input
		istringstream si("");
		ostringstream so;
		sumlines(si, so);
		assert(so.str().empty());
	}
	{ // One Line, One Value
		istringstream si("42");
		ostringstream so;
		sumlines(si, so);
		assert(so.str() == "42\n");
	}
	{ // With Negative Value
		istringstream si("-10 12");
		ostringstream so;
		sumlines(si, so);
		assert(so.str() == "2\n");
	}
}
#endif

