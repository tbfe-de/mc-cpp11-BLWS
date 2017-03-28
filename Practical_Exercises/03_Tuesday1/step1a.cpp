/*
 * Erkennen von Leerzeilen und ungueltigen Eingaben
 * als Erweiterung zu: Variations/Sumlines/step1.cpp
 * (siehe aufgabe.txt Abschnitt 1)
*/
#include <iostream>
#include <sstream>
#include <string>

void sumlines(std::istream &in, std::ostream &out) {
	std::string line;
	while (std::getline(in, line)) {
		if (line.find_first_not_of(" \\t") == std::string::npos)
			continue;
		std::istringstream iss(line + " ");
		int sum = 0;
		int ival;
		while ((iss >> ival)
		    && (iss.peek() == ' ' || iss.peek() == '\t'))
			sum += ival;
		if (iss.eof())
			out << sum << '\n';
		else
			out << "EFMT: " << line << std::endl;
	}
}

#define TDD
#ifndef TDD
int main() {
	sumlines(std::cin, std::cout);
}
#else
#include "PT.h"
int main() {
	using namespace std;
	cout << "Note: no news is good news :-)" << endl;

	{ // Typical Example	     //	INPUT SUPPLIED
				     // --------------------
		istringstream si(	"3 4 5"		"\n"
		 			"7 8"		"\n"
					"   "  		"\n"
					"9 10 11 12"	"\n"
							"\n"
					"17"		"\n");
		ostringstream so;    // OUTPUT EXPECTED	
		sumlines(si, so);    // --------------------
		T_(so.str(),		"12"		"\n"
					"15"		"\n"
					"42"		"\n"
					"17"		"\n");
	}
	{ // Empty Input
		istringstream si("");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "");
	}
	{ // One Line, One Value
		istringstream si("42");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "42\n");
	}
	{ // With Negative Value
		istringstream si("-10 12");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "2\n");
	}
	{ // Formatting Error
		istringstream si("-10+12");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "EFMT: -10+12\n");
	}
}
#endif

