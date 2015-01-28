#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <boost/optional.hpp>

enum class InputType : unsigned { String, Long, Double };

bool getword(std::istream &is, std::string &strval,
             boost::optional<long> &longval,
	     boost::optional<double> &doubleval) {
	if (!(is >> strval).good())
		return false;
	char *ep;
	const auto lv = std::strtol(strval.c_str(), &ep, 10);
	if (*ep == '\0') longval = lv;
	const auto dv = std::strtod(strval.c_str(), &ep);
	if (*ep == '\0') doubleval = dv;
	return true;
}

void multitype(std::istream &in, std::ostream& out) {
	std::vector<std::tuple<void *, InputType>> v;
	long lmax = 0; 
	double dmax = 0.0;
	std::string smax = "";
	std::string word;
	boost::optional<long> lval;
	boost::optional<double> dval;
	while (getword(in, word, lval, dval)) {
		if (lval) {
			v.push_back(std::make_tuple(new long(lval.get()), InputType::Long));
			if (lmax < lval.get()) lmax = lval.get();
		}
		else if (dval) {
			v.push_back(std::make_tuple(new double(dval.get()), InputType::Double));
			if (dmax < dval.get()) dmax = dval.get();
		}
		else {
			v.push_back(std::make_tuple(new std::string(word), InputType::String));
			if (smax < word) smax = word;
		}
	}
	for (auto it = v.begin(); it != v.end(); ++it) {
		auto ptr = std::get<0>(*it);
		switch (std::get<1>(*it)) {
			case InputType::Long: {
				const auto p = reinterpret_cast<long *>(ptr);
				out << *p << ((*p == lmax) ? " <---\n" : "\n");
				delete p;
				break;
			}
			case InputType::Double: {
				const auto p = reinterpret_cast<double *>(ptr);
				out << *p << ((*p == dmax) ? " <---\n" : "\n");
				delete p;
				break;
			}
			case InputType::String: {
				const auto p = reinterpret_cast<std::string *>(ptr);
				out << *p << ((*p == smax) ? " <---\n" : "\n");
				delete p;
				break;
			}
		}
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
