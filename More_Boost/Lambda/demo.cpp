#include <boost/lambda/lambda.hpp>
 	using boost::lambda::_1;
	using boost::lambda::_2;

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "Util/CK/CK.h"

void process(istream &is, ostream &os) {
	vector<int> v;
	copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(v));

	vector<const int *> vp_up(v.size());
	transform(v.begin(), v.end(), vp_up.begin(), &_1);
	sort(vp_up.begin(), vp_up.end(), *_1 < *_2); 
	for_each(vp_up.begin(), vp_up.end(), os << *_1 << ' '); os << endl;

	vector<const int *> vp_down(v.size());
	transform(v.begin(), v.end(), vp_down.begin(), &_1);
	sort(vp_down.begin(), vp_down.end(), *_1 > *_2);
	for_each(vp_down.begin(), vp_down.end(), os << *_1 << ' '); os << endl;
}

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

