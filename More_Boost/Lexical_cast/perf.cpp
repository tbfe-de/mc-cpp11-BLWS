#include <cassert>
#include <string>
#include <boost/lexical_cast.hpp>

#include "Util/CxTime/CXTIME.h"

int main() {
	const std::string strval("7654221");
	const long numval = 7654221;
	
	CXTIME("Conversion from string via 'std::string' operations",
			long n;
		,
			n = 0;
			for (int i = 0; i < strval.length(); ++i)
				n = 10*n + strval[i] - '0';
		,
			assert(n == numval);
		,
			cxtime_pessimize(&n);
	)

	CXTIME("Conversion from string via 'boost::lexical_cast'",
			long n;
		,
			n = boost::lexical_cast<long>(strval);
		,
			assert(n == numval);
		,
	)

	CXTIME("Conversion to string via 'std::string' operations",
			std::string s;
		,
			unsigned long u = numval;
			s.reserve((37 * sizeof u) / 10);
			char b[2];
			b[1] = '\0';
			do {
				b[0] = static_cast<char>((u % 10) + '0');
				s.insert(0, b);
			} while ((u /= 10) > 0);
		,
			assert(s == strval);
		,
	)

	CXTIME("Conversion to string via 'std::string' operations - optimized",
			std::string s;
		,
			unsigned long u = numval;
			s.reserve((37 * sizeof u) / 10);
			char c;
			do {
				c = static_cast<char>((u % 10) + '0');
				s.append(&c, 1);
			} while ((u /= 10) > 0);
			std::string::iterator b = s.begin();
			std::string::iterator e = s.end();
			while (b < e) (c = *b, *b++ = *--e, *e = c);
		,
			assert(s == strval);
		,
	)

	CXTIME("Conversion to string via 'boost::lexical_cast' -- constructor",
		,
			std::string s(boost::lexical_cast<std::string>(numval));
		,
			assert(s == strval);
		,
	)

	CXTIME("Conversion to string via 'boost::lexical_cast' -- assignment",
			std::string s;
		,
			s = boost::lexical_cast<std::string>(numval);
		,
			assert(s == "7654221");
		,
	)

	CXTIME("Conversion to wstring via 'boost::lexical_cast' -- assignment",
			std::wstring s;
		,
			s = boost::lexical_cast<std::wstring>(numval);
		,
			assert(s == L"7654221");
		,
	)

}
