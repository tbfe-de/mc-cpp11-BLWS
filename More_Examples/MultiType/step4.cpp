#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

class Input {
public:
	static long lmax;
	static double dmax;
	static std::string smax;
	class Long;
	class Double;
	class String;
	virtual ~Input() {}
	virtual void print(std::ostream &) =0;
};
long Input::lmax = 0L;
double Input::dmax = 0.0;;
std::string Input::smax = "";

class Input::Long : public Input {
	const long val;
public:
	Long(long v) : val(v) {}
	virtual void print(std::ostream &os) {
		os << val << ((val == lmax) ? " <---\n" : "\n");
	}
};

class Input::Double : public Input {
	const double val;
public:
	Double(double v) : val(v) {}
	virtual void print(std::ostream &os) {
		os << val << ((val == dmax) ? " <---\n" : "\n");
	}
};

class Input::String : public Input {
	const std::string val;
public:
	String(const std::string &v) : val(v) {}
	virtual void print(std::ostream &os) {
		os << val << ((val == smax) ? " <---\n" : "\n");
	}
};

bool getword(std::istream &is, std::string &strval,
             boost::optional<long> &longval,
	     boost::optional<double> &doubleval) {
	if (!(is >> strval).good())
		return false;
	try { longval = boost::lexical_cast<long>(strval); }
	catch (boost::bad_lexical_cast &) {}
	try { doubleval = boost::lexical_cast<double>(strval); }
	catch (boost::bad_lexical_cast &) {}
	return true;
}
void multitype(std::istream &in, std::ostream& out) {
	std::vector<Input *> v;
	std::string word;
	boost::optional<long> lval;
	boost::optional<double> dval;
	while (getword(in, word, lval, dval)) {
		if (lval) {
			v.push_back(new Input::Long(lval.get()));
			if (Input::lmax < lval.get()) Input::lmax = lval.get();
		}
		else if (dval) {
			v.push_back(new Input::Double(dval.get()));
			if (Input::dmax < dval.get()) Input::dmax = dval.get();
		}
		else {
			v.push_back(new Input::String(word));
			if (Input::smax < word) Input::smax = word;
		}
	}
	for (auto &p : v) {
		p->print(out);
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
