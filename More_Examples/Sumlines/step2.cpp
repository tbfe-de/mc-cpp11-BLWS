#include <iostream>
#include <sstream>
#include <string>

void sumlines(std::istream &in, std::ostream &out) {
	enum { WS, IVAL } state = WS;
	int sum = 0;
	int ival;
	bool minus;
	char ch;
	while (in.get(ch)) {
		switch (state) {
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
				break;
			case IVAL:
				if ('0' <= ch && ch <= '9')
					ival = 10*ival + ch - '0';
				else {
					if (minus)
						sum -= ival;
					else
						sum += ival;
					state = WS;
				}
				break;
			}
			if (ch == '\n') {
				out << sum << '\n';
				sum = 0;
			}
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
	cout << "... only no news is good news :-/ ..." << endl;

	{ // Typical Example	     //	SUPPLIED INPUT
				     // --------------------
		istringstream si(	"3 4 5"		"\n"
		 			"7 8"		"\n"
					"9 10 11 12"	"\n"
					"17"		"\n");
		ostringstream so;    // EXPECTED OUTPUT
		sumlines(si, so);    // --------------------
		assert(so.str() ==	"12"		"\n"
					"15"		"\n"
					"42"		"\n"
					"17"		"\n");
	}
	{ // Empty Input
		istringstream si;
		ostringstream so;
		sumlines(si, so);
		assert(so.str().empty());
	}
	{ // One Line, One Value
		istringstream si("42\n");
		ostringstream so;
		sumlines(si, so);
		assert(so.str() == "42\n");
	}
	{ // With Negative Value
		istringstream si("-10 12\n");
		ostringstream so;
		sumlines(si, so);
		assert(so.str() == "2\n");
	}
}
#endif

