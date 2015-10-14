/*
 * Fehlerbehandlung auch für Gleitpunktzahlen
 * mit Erkennung durch boost::lexical_cast als
 * Erweiterung zu: Variations/Sumlines/step3.cpp
 * (siehe aufgabe.txt Abschnitt 3b)
*/
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/io/ios_state.hpp>
#include <boost/lexical_cast.hpp>

void sumlines(std::istream &in, std::ostream &out) {
	boost::io::ios_all_saver io_all(out);
	std::string line;
	out.setf(std::ios::fixed, std::ios::floatfield);
	while (std::getline(in, line)) {
		try {
			double sum = 0.0;
			std::istringstream iss(line);
			std::string item;
			while (iss >> item) {
				sum += boost::lexical_cast<double>(item);
			}
			if (static_cast<long long>(sum) == sum)
				out.precision(0);
			else
				out.precision(2);
			out << sum << '\n';
		}
		catch (boost::bad_lexical_cast &) {
			out << "EFMT: " << line << '\n';
		}
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
			     // ----------------------------
	istringstream si(	"0.10 2.43 5.50"	"\n"
				"12.30 1"		"\n"
				"4.40"			"\n"
				"3.00"			"\n"
				"0.04"			"\n");
	ostringstream so;    // OUTPUT EXPECTED	
	sumlines(si, so);    // --------------------
	T_(so.str(),		"8.03"		"\n"
				"13.30"		"\n"
				"4.40"		"\n"
				"3"		"\n"
				"0.04"		"\n");
}

void empty_input() {
	using namespace std;
	istringstream si("");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "");
}

void with_negative_value() {
	using namespace std;
	istringstream si("2 -1.50\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "0.50\n");
}

void input_format_error() {
	using namespace std;
	istringstream si("2,00\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "EFMT: 2,00\n");
}

void keeping_format_state() {
	using namespace std;
	istringstream si;
	ostringstream so;
	const auto flags = so.flags();
	const auto precision = so.precision();
	const auto fill = so.fill();
	sumlines(si, so);
	T_(so.flags(), flags);
	T_(so.precision(), precision);
	T_(so.fill(), fill);
}


int main() {
	using namespace std;
	cout << "... only no news is good news :-/ ..." << endl;

	typical_example();
	empty_input();
	with_negative_value();
	input_format_error();
	keeping_format_state();
}
#endif

