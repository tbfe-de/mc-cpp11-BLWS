#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>

struct MarkingPrinter : public boost::static_visitor<> {
	std::ostream &os;
public:
	MarkingPrinter(std::ostream &os_) : os(os_) {}
	void operator()(long val) const {
		os << val << ((val == lmax) ? " <---\n" : "\n");
	}
	void operator()(double val) const {
		os << val << ((val == dmax) ? " <---\n" : "\n");
	}
	void operator()(const std::string &val) const {
		os << val << ((val == smax) ? " <---\n" : "\n");
	}
	static long lmax;
	static double dmax;
	static std::string smax;
};

long MarkingPrinter::lmax = 0; 
double MarkingPrinter::dmax = 0.0;
std::string MarkingPrinter::smax = "";

void multitype(std::istream &in, std::ostream& out) {
	std::vector<boost::variant<long, double, std::string>> v;
	std::string word;
	while (in >> word) {
		try {
			const auto val = boost::lexical_cast<long>(word);
			v.push_back(val);
			if (MarkingPrinter::lmax < val) MarkingPrinter::lmax = val;
			continue;
		} catch (boost::bad_lexical_cast &) {}
		try {
			const auto val = boost::lexical_cast<double>(word);
			v.push_back(val);
			if (MarkingPrinter::dmax < val) MarkingPrinter::dmax = val;
			continue;
		} catch (boost::bad_lexical_cast &) {}
		try {
			const auto val = boost::lexical_cast<std::string>(word);
			v.push_back(val);
			if (MarkingPrinter::smax < val) MarkingPrinter::smax = val;
			continue;
		} catch (boost::bad_lexical_cast &) {}
	}
	for (const auto &e : v)
		boost::apply_visitor(MarkingPrinter(out), e);
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
