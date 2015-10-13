/*
 * Verwendung von Boost.IOState_saver
 *
 * (siehe aufgabe.txt Abschnitt 1)
*/

#include <iostream>
#include <sstream>
#include <string>
#include <boost/io/ios_state.hpp>

void sumlines(std::istream &in, std::ostream &out) {
	boost::io::ios_all_saver io_all(out);
	std::string line;
	out.setf(std::ios::fixed, std::ios::floatfield);
	out.precision(2);
	while (std::getline(in, line)) {
		float sum = 0.0;
		std::istringstream iss(line);
		float ival;
		while (iss >> ival)
			sum += ival;
		out << sum << '\n';
	}
}

#ifndef TDD
int main() {
	sumlines(std::cin, std::cout);
}
#else
#include "PT.h"
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
	T_(so.str(),		"12.93"		"\n"
				"15.90"		"\n"
				"42.00"		"\n"
				"17.50"		"\n");
}

void empty_input() {
	using namespace std;
	istringstream si("");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "");
}

void one_line_one_value() {
	using namespace std;
	istringstream si("4.2\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "4.20\n");
}

void with_negative_value() {
	using namespace std;
	istringstream si("-10 12");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "2.00\n");
}

void keeping_format_state() {
	using namespace std;
	istringstream si;
	ostringstream so;
	so.setf(std::ios::scientific, std::ios::floatfield);
	so.precision(6);
	sumlines(si, so);
	T_(so.flags() & std::ios::floatfield, ios::scientific);
	T_(so.precision(), 6);
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

