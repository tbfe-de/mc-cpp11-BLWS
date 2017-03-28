/*
 * Aufsummieren von Zeitspannen
 * (siehe aufgabe.txt Abschnitt 2)
*/
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/io/ios_state.hpp>
#include <boost/regex/v4/regex.hpp>

const std::string hhmm{"(-?)([0-9]+):([0-5][0-9])"};
const std::string hhmmss = hhmm + ":([0-5][0-9])";

void sumlines(std::istream &in, std::ostream &out) {
	boost::io::ios_all_saver io_all(out);
	std::string line;
	out.fill('0');
	boost::regex re_hhmm{::hhmm};
	boost::regex re_hhmmss{::hhmmss};
	while (std::getline(in, line)) {
		try {
			std::chrono::seconds sum;
			std::istringstream iss(line);
			std::string item;
			while (iss >> item) {
				boost::smatch n_hhmmss;
				if (!boost::regex_match(item, n_hhmmss, re_hhmmss)
				 && !boost::regex_match(item, n_hhmmss, re_hhmm))
					throw nullptr;
				std::chrono::seconds tmp
					= std::chrono::hours(std::stoll(n_hhmmss[2]))
					+ std::chrono::minutes(std::stoi(n_hhmmss[3]));
				if (n_hhmmss.size() > 4)
					tmp += std::chrono::seconds(std::stoi(n_hhmmss[4]));
				if (n_hhmmss[1] == "-")
					tmp *= -1;
				sum += tmp;
			}
			namespace sc = std::chrono;
			out << sc::duration_cast<sc::hours>(sum).count()
                            << ':' << std::setw(2)
			    << sc::duration_cast<sc::minutes>(sum % sc::hours(1)).count();
			if (auto secs = (sum % sc::minutes(1)).count())
                        	out << ':' << std::setw(2) << secs;
			out << '\n';
		}
		catch (std::nullptr_t) {
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
	istringstream si(	"1:20:10 2:43:05"	"\n"
				"12:03 1:05"		"\n"
				"1:01:02 2:02 3:03:59"	"\n"
				"4:04"			"\n"
				"0:04:00"		"\n");
	ostringstream so;    // OUTPUT EXPECTED	
	sumlines(si, so);    // --------------------
	T_(so.str(),		"4:03:15"	"\n"
				"13:08"		"\n"
				"6:07:01"	"\n"
				"4:04"		"\n"
				"0:04"		"\n");
}

void empty_input() {
	using namespace std;
	istringstream si("");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "");
}

void wrap_at_full_day() {
	using namespace std;
	istringstream si("3:59:59 0:00:01\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "4:00\n");
}

void with_negative_value() {
	using namespace std;
	istringstream si("2:00 -1:05\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "0:55\n");
}

void input_format_error() {
	using namespace std;
	istringstream si("2:00 +1:05\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "EFMT: 2:00 +1:05\n");
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
	wrap_at_full_day();
	with_negative_value();
	input_format_error();
	keeping_format_state();
}
#endif

