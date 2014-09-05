#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "CXTIME.h"

void myItoa(char *bp, unsigned numval) {
	char *cp = bp;
	do {
		*cp++ = numval % 10 + '0';
	} while ((numval /= 10) != 0);
	*cp = '\0';
	register char tmp;
	while (--cp > bp) {
		tmp = *bp;
		*bp++ = *cp;
		*cp = tmp;
	}
}

int main() {

	const int numval = 7654221;
	
	CXTIME("Conversion via 'sprintf'",
			char s[20];
		,
			std::sprintf(s, "%d", numval);
		,
			assert(std::strcmp(s, "7654221") == 0);
		,
	)

	CXTIME("Conversion via 'snprintf'",
			char s[20];
		,
			std::snprintf(s, (sizeof s) - 1, "%d", numval);
		,
			assert(strcmp(s, "7654221") == 0);
		,
	)

	CXTIME("Conversion via hand-written function",
			char s[20];
		,
			myItoa(s, numval);
		,
			assert(strcmp(s, "7654221") == 0);
		,
	)

	CXTIME("Conversion via 'std::string' operations",
			std::string s;
		,
			unsigned u = numval;
			do {
				char b[2];
				b[0] = static_cast<char>((u % 10) + '0');
				b[1] = '\0';
				s.insert(0, b);
			} while ((u /= 10) > 0);
		,
			assert(s == "7654221");
		,
	)

	CXTIME("Conversion via 'std::ostringstream'",
			std::string s;
		,
			std::ostringstream os;
			os << numval;
			s = os.str();
		,
			assert(s == "7654221");
		,
	)
}
