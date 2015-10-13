#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/io/ios_state.hpp>
#include <boost/regex/v4/regex.hpp>

void euro_grouped(std::ostream &os, long long eur) {
	// boost::io::ios_all_saver io_all(os);
	if (eur < 1000)
		os << eur;
	else {
		euro_grouped(os, eur / 1000);
		os << '.' << std::setfill('0') << std::setw(3) << (eur % 1000);
	}
}

void sumlines(std::istream &in, std::ostream &out) {
	boost::io::ios_all_saver io_all(out);
	std::string line;
	out.setf(std::ios::fixed, std::ios::floatfield);
	boost::regex re_euro("(-?\\d{1,3}(?:[.]\\d{3})*)" // full euro
			     "(?:[,](?:-|(\\d{2})))?");   // opt. cent
	while (std::getline(in, line)) {
		try {
			long long sum = 0;
			std::istringstream iss(line);
			std::string item;
			while (iss >> item) {
				using boost::regex;
				using boost::regex_match;
				using boost::regex_replace;
				using boost::smatch;
				using std::string;
				using std::stoi;
				using std::stoll;
				smatch euro_cent;
				if (!regex_match(item, euro_cent, re_euro))
					throw nullptr;
				const string euros = euro_cent[1];
				const string cents = euro_cent[2];
				auto tmp = 100*stoll(regex_replace(euros, regex("[.]"), ""));
				if (!cents.empty()) {
					if (tmp < 0)
						tmp -= stoi(cents);
					else
						tmp += stoi(cents);
				}
				sum += tmp;
			}
			if (sum < 0) {
				out << '-';
				sum = -sum;
			}
			euro_grouped(out, sum / 100);
			if (const auto c = sum % 100)
				out << ',' << std::setfill('0') << std::setw(2) << c;
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
	istringstream si(	"0,10 2,43 5,50"	"\n"
				"1.234,30 1"		"\n"
				"1.234.567"		"\n"
				"3,-"			"\n"
				"0,04"			"\n");
	ostringstream so;    // OUTPUT EXPECTED	
	sumlines(si, so);    // --------------------
	T_(so.str(),		"8,03"		"\n"
				"1.235,30"	"\n"
				"1.234.567"	"\n"
				"3"		"\n"
				"0,04"		"\n");
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
	istringstream si("2 -1,50\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "0,50\n");
}

void input_format_error() {
	using namespace std;
	istringstream si("2.00\n");
	ostringstream so;
	sumlines(si, so);
	T_(so.str(), "EFMT: 2.00\n");
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

