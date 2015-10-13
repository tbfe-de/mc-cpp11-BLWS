#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/variant.hpp>

void multitype(std::istream &in, std::ostream& out) {
	std::vector<boost::variant<long, double, std::string>> v;
	long lmax = 0; 
	double dmax = 0.0;
	std::string smax = "";
	std::string word;
	while (in >> word) {
		char *ep;
		const long lval = std::strtol(word.c_str(), &ep, 10);
		if (*ep == '\0') {
			v.push_back(lval);
			if (lmax < lval) lmax = lval;
		}
		else {
			const double dval = strtod(word.c_str(), &ep);
			if (*ep == '\0') {
				v.push_back(dval);
				if (dmax < dval) dmax = dval;
			}
			else {
				v.push_back(word);
				if (smax < word) smax = word;
			}
		}
	}
	for (auto &e : v) {
		if (auto *p = boost::get<long>(&e))
			out << *p << ((*p == lmax) ? " <---\n" : "\n");
		else if (auto *p = boost::get<double>(&e))
			out << *p << ((*p == dmax) ? " <---\n" : "\n");
		else if (auto *p = boost::get<std::string>(&e))
			out << *p << ((*p == smax) ? " <---\n" : "\n");
	}
}

#ifndef TDD
int main() {
	multitype(std::cin, std::cout);
}
#else
#include <sstream>
int main() {
	using namespace std;
	istringstream some_input("12 1.4 abd 34 17.77 def ghi 34 12 4.6");
	ostringstream tst_output;
	multitype(some_input, tst_output);
	if (tst_output.str() ==	"12"		"\n"
				"1.4"		"\n"
				"abd"		"\n"
				"34 <---"	"\n"
				"17.77 <---"	"\n"
				"def"		"\n"
				"ghi <---"	"\n"
				"34 <---"	"\n"
				"12"		"\n"
				"4.6"		"\n")
		cout << "*** TEST PASSED" << endl;
}
#endif
