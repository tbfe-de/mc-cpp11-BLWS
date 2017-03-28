/*
 * Erkennen von Leerzeilen und ungueltigen Eingaben
 * als Erweiterung zu: Variations/Sumlines/step2.cpp
 * (siehe aufgabe.txt Abschnitt 1)
*/
#include <iostream>
#include <sstream>
#include <string>

void sumlines(std::istream &in, std::ostream &out) {
	enum { IWS, WS, IVAL, EFMT } state = IWS;
	int sum = 0;
	int ival;
	bool minus;
	char ch;
	while (in.get(ch)) {
		switch (state) {
			case IWS:
				if (ch == ' ' || ch == '\t' || ch == '\n')
					continue;
				/*FALLTHROUGH*/
			case WS:
				if ('0' <= ch && ch <= '9') {
					ival = ch - '0';
					minus = false;
					state = IVAL;
				}
				else if (ch == '-') {
					ival = 0;
					minus = true;
					state = IVAL;
				}
				else if (ch != ' ' && ch != '\t' && ch != '\n')
					state = EFMT;
				break;
			case IVAL:
				if ('0' <= ch && ch <= '9')
					ival = 10*ival + ch - '0';
				else if (ch == ' ' || ch == '\t' || ch == '\n') {
					if (minus)
						sum -= ival;
					else
						sum += ival;
					state = WS;
				}
				else state = EFMT;
				break;
			case EFMT:
				break;
		}
		if (ch == '\n') {
			if (state == EFMT)
				out << "Format Error!\n";
			else if (state != IWS)
				out << sum << '\n';
			state = IWS;
			sum = 0;
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
		istringstream si(	"3 4 5"		"\n"
		 			"7 8"		"\n"
					"   "		"\n"
					"9 10 11 12"	"\n"
							"\n"
					"17"		"\n");
		ostringstream so;    // EXPECTED OUTPUT
		sumlines(si, so);    // --------------------
		T_(so.str(),		"12"		"\n"
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
	{ // Formatting Error
		istringstream si("-10+12\n");
		ostringstream so;
		sumlines(si, so);
		T_(so.str(), "Format Error!\n");
	}
}
#endif

