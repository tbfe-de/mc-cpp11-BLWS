#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <vector>
	using namespace std;

struct GetAddress {
	const int *operator()(const int &elem) { return &elem; }
};
struct Lt_Compare {
	bool operator()(const int *lhs, const int *rhs) { return *lhs < *rhs; }
};
struct Gt_Compare {
	bool operator()(const int *lhs, const int *rhs) { return *lhs > *rhs; }
};
struct PtrPrinter {
	PtrPrinter(ostream &_os) : os(_os) {}
	void operator()(const int *elem) { os << *elem << ' '; }
private:
	ostream &os;
};

void process(istream &is, ostream &os) {
	vector<int> v;
	copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(v));

	vector<const int *> vp_up(v.size());
	transform(v.begin(), v.end(), vp_up.begin(), GetAddress());
	sort(vp_up.begin(), vp_up.end(), Lt_Compare()); 
	for_each(vp_up.begin(), vp_up.end(), PtrPrinter(os));
	os << endl;

	vector<const int *> vp_down(v.size());
	transform(v.begin(), v.end(), vp_down.begin(), GetAddress());
	sort(vp_down.begin(), vp_down.end(), Gt_Compare());
	for_each(vp_down.begin(), vp_down.end(), PtrPrinter(os));
	os << endl;
}

#include "Util/CK/CK.h"

int main() {


	{
CK_section(	"Empty input ..................."		)
		istringstream is("");
		ostringstream os;
		process(is, os);
CK_compare(	os.str(),	""			"\n"
				""			"\n"	);
	}

	{
CK_section(	"Single input .................."		)
		istringstream is("1");
		ostringstream os;
		process(is, os);
CK_compare(	os.str(),	"1 " "\n"
				"1 " "\n"			);
	}

	{
CK_section(	"All equal input ..............."		)
		istringstream is("2 2 2");
		ostringstream os;
		process(is, os);
CK_compare(	os.str(),	"2 2 2 " 		"\n"
				"2 2 2 " 		"\n"	);
	}

	{
CK_section(	"Realistic input ..............."		)
		istringstream is("1 5 -3 1 9 7 0 -2 6");
		ostringstream os;
		process(is, os);
CK_compare(	os.str(),	"-3 -2 0 1 1 5 6 7 9 "	"\n"
				"9 7 6 5 1 1 0 -2 -3 "	"\n"	);
	}

}

