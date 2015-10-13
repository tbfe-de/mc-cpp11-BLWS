#include <iostream>
#include <sstream>
#include <string>

void sumlines(std::istream &in, std::ostream &out) {
	std::string line;
	const auto flags = out.setf(std::ios::fixed, std::ios::floatfield);
	const auto precision = out.precision(2);
	while (std::getline(in, line)) {
		float sum = 0.0;
		std::istringstream iss(line);
		float ival;
		while (iss >> ival)
			sum += ival;
		out << sum << '\n';
	}
	out.precision(precision);
	out.flags(flags);
}

#define TDD
#ifndef TDD
int main() {
	sumlines(std::cin, std::cout);
}
#else
#include <cassert>
void typical_example() {
	using namespace std;
		   	     //	INPUT SUPPLIED
			     // --------------------
	istringstream si(	"3 4.20 5.73"	"\n"
				"7 8.90"	"\n"
				"9 10 11 12"	"\n"
				"17.5"		"\n");
	ostringstream so;    // OUTPUT EXPECTED	
	sumlines(si, so);    // --------------------
	assert(so.str() ==	"12.93"		"\n"
				"15.90"		"\n"
				"42.00"		"\n"
				"17.50"		"\n");
}

void empty_input() {
	using namespace std;
	istringstream si("");
	ostringstream so;
	sumlines(si, so);
	assert(so.str().empty());
}

void one_line_one_value() {
	using namespace std;
	istringstream si("4.2\n");
	ostringstream so;
	sumlines(si, so);
	assert(so.str() == "4.20\n");
}

void with_negative_value() {
	using namespace std;
	istringstream si("-10 12");
	ostringstream so;
	sumlines(si, so);
	assert(so.str() == "2.00\n");
}

void keeping_format_state() {
	using namespace std;
	istringstream si;
	ostringstream so;
	so.setf(std::ios::scientific);
	so.precision(6);
	sumlines(si, so);
	assert(so.flags() & ios::scientific);
	assert(so.precision() == 6);
}


int main() {
	using namespace std;
	cout << "... only no news is good news :-/ ..." << endl;

	typical_example();
	empty_input();
	one_line_one_value();
	with_negative_value();
	keeping_format_state();
}
#endif

