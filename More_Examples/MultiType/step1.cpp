#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

enum InputType {
	InputType_String = (1u<<0),
	InputType_Long   = (1u<<1),
	InputType_Double = (1u<<2)
};

unsigned getword(std::istream &is, std::string &strval,
                 long &longval, double &doubleval) {
	unsigned result = 0u;
	if (is >> strval) {
		result |= unsigned(InputType_String);
		char *ep;
		longval = std::strtol(strval.c_str(), &ep, 10);
		if (*ep == '\0')
			result |= unsigned(InputType_Long);
		doubleval = std::strtod(strval.c_str(), &ep);
		if (*ep == '\0')
			result |= unsigned(InputType_Double);
	}
	return result;
}

struct InputData {
	void *data;
	InputType type;
	InputData(void *data_, InputType type_)
		: data(data_), type(type_)
	{}
};

std::vector<InputData> v;

void multitype(std::istream &in, std::ostream& out) {
	long lmax = 0; 
	double dmax = 0.0;
	std::string smax = "";
	std::string word;
	long lval;
	double dval;
	unsigned success;
	while ((success = getword(in, word, lval, dval)) != 0) {
		if (success & unsigned(InputType_Long)) {
			v.push_back(InputData(new long(lval), InputType_Long));
			if (lmax < lval) lmax = lval;
		}
		else if (success & unsigned(InputType_Double)) {
			v.push_back(InputData(new double(dval), InputType_Double));
			if (dmax < dval) dmax = dval;
		}
		else {
			v.push_back(InputData(new std::string(word), InputType_String));
			if (smax < word) smax = word;
		}
	}
	for (auto it = v.begin(); it != v.end(); ++it) {
		switch (it->type) {
			case InputType_Long: {
				const auto p = reinterpret_cast<long *>(it->data);
				out << *p << ((*p == lmax) ? " <---\n" : "\n");
				delete p;
				break;
			}
			case InputType_Double: {
				const auto p = reinterpret_cast<double *>(it->data);
				out << *p << ((*p == dmax) ? " <---\n" : "\n");
				delete p;
				break;
			}
			case InputType_String: {
				const auto p = reinterpret_cast<std::string *>(it->data);
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
