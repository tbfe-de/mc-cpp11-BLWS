#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "CXTIME.h"

int main() {
	const std::string strval("7654221");

	CXTIME("Conversion via 'atol'",
			long n;
		,
			n = atol(strval.c_str());
		,
			assert(n == 7654221);
		,
			cxtime_pessimize(&n);
	)

	CXTIME("Conversion via 'strtol'",
			long n;
			char *ep_notused;
		,
			n = strtol(strval.c_str(), &ep_notused, 10);
		,
			assert(n == 7654221);
		,
			cxtime_pessimize(&n);
	)

	CXTIME("Conversion via 'explicit loop' -- using at()",
			long n;
		,
			n = 0;
			for (int i = 0; i < strval.length(); ++i)
				n = 10*n + strval.at(i) - '0';
		,
			assert(n == 7654221);
		,
			cxtime_pessimize(&n);
	)

	CXTIME("Conversion via 'explicit loop' -- using operator[]",
			long n;
		,
			n = 0;
			for (int i = 0; i < strval.length(); ++i)
				n = 10*n + strval[i] - '0';
		,
			assert(n == 7654221);
		,
			cxtime_pessimize(&n);
	)

	CXTIME("Conversion via 'std::istringstream' -- long version",
			long n;
		,
			std::istringstream is;
			is.str(strval);
			is >> n;
		,
			assert(n == 7654221);
		,
			cxtime_pessimize(&n);
	)

	CXTIME("Conversion via 'std::istringstream' -- short version",
			long n;
		,
			std::istringstream(strval) >> n;
		,
			assert(n == 7654221);
		,
			cxtime_pessimize(&n);
	)
}
