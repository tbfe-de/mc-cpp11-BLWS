/*
 * Verarbeitung von Gleitpunktzahlen als Erweiterung zu:
 * Variations/Sumlines/step2.cpp
 * (siehe aufgabe.txt Abschnitt 2)
*/
#include <iostream>
#include <sstream>
#include <string>

void sumlines(std::istream &in, std::ostream &out) {
	enum { WS, FVAL } state = WS;
	double sum = 0.0;
	double frac = 1.0;
	double fval;
	bool minus;
	char ch;
	while (in.get(ch)) {
		switch (state) {
			case WS:
				if ('0' <= ch && ch <= '9') {
					fval = ch - '0';
					minus = false;
					state = FVAL;
				}
				else if (ch == '-') {
					fval = 0.0;
					minus = true;
					state = FVAL;
				}
				break;
			case FVAL:
				if (ch == '.')
					frac *= 10.0;
				else if ('0' <= ch && ch <= '9') {
					if (frac == 1.0)
						fval = 10*fval + (ch - '0');
					else {
						fval += (ch - '0') / frac;
						frac *= 10.0;
					}
				}
				else {
					if (minus)
						sum -= fval;
					else
						sum += fval;
					state = WS;
					frac = 1.0;
				}
				break;
			}
			if (ch == '\n') {
				out << sum << '\n';
				sum = 0.0;
			}
		}
		
 }

#ifndef TDD
int main() {
	sumlines(std::cin, std::cout);
}
#else
#include "PT.h"
int main() {
	using namespace std;
	cout << "... only no news is good news :-/ ..." << endl;

	{ // Typical Example	     //	SUPPLIED INPUT
				     // --------------------
		istringstream si(	"3.1 4.22 5"	"\n"
		 			"7 8"		"\n"
					"9 10 11 12"	"\n"
					"17"		"\n");
		ostringstream so;    // EXPECTED OUTPUT
		sumlines(si, so);    // --------------------
		T_(so.str(),		"12.32"		"\n"
					"15"		"\n"
					"42"		"\n"
					"17"		"\n");
	}
	{ // Empty Input
		istringstream si;
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "");
	}
	{ // One Line, One Value
		istringstream si("42\n");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "42\n");
	}
	{ // With Negative Value
		istringstream si("-10 12\n");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "2\n");
	}
}
#endif

