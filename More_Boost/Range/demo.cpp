#include <iterator>
	using std::ostream_iterator;
#include <sstream>
	using std::ostringstream;
#include <vector>
	using std::vector;

#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/irange.hpp>

#include "Util/CK/CK.h"


int main() {
		/////////////////////////////////////////////////////////
CK_section(	"Basic Use ..........................................."	)
		{ 
		ostringstream os;
		vector<int> v;
		v.push_back(7);
		v.push_back(2);
		v.push_back(12);
		os << "in: ";
		boost::copy(v, ostream_iterator<int>(os, " "));
		os << "out: ";
		boost::sort(v);
		boost::copy(v, ostream_iterator<int>(os, " "));
		// boost::copy(boost::sort(v), ostream_iterator<int>(os, " "));
CK_compare(	os.str(),	"in: 7 2 12 out: 2 7 12 ")
		}
		int data[]= { 3, 7, 17, -9, 8, 7, 0, 5, 5, -1, 0, 3, 2 };
		{ 
		ostringstream os;
		boost::copy(
			data,
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "3;7;17;-9;8;7;0;5;5;-1;0;3;2;"	)
		}

CK_section(	"Adaptors basics ....................................."	)
		{
		ostringstream os;
		boost::copy(
			boost::adaptors::reverse(data),
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "2;3;0;-1;5;5;0;7;8;-9;17;7;3;"	)
		}
		{
		ostringstream os;
		boost::copy(
			data | boost::adaptors::reversed,
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "2;3;0;-1;5;5;0;7;8;-9;17;7;3;"	)
		}
		{
		ostringstream os;
		boost::copy(
			boost::adaptors::unique(data),
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "3;7;17;-9;8;7;0;5;-1;0;3;2;"	)
		}
		{
		ostringstream os;
		boost::copy(
			data | boost::adaptors::uniqued,
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "3;7;17;-9;8;7;0;5;-1;0;3;2;"	)
		}

CK_section(	"Combining adaptors..................................."	)
		{
		using namespace boost::adaptors;
		ostringstream os;
		boost::copy(
			data | reversed | uniqued,
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "2;3;0;-1;5;0;7;8;-9;17;7;3;"		)
		}
		{
		namespace ba= boost::adaptors;
		ostringstream os;
		boost::copy(
			ba::unique(ba::reverse(data)),
			ostream_iterator<int>(os, ";")
		);
CK_compare(	os.str()	, "2;3;0;-1;5;0;7;8;-9;17;7;3;"		)
		}

CK_section(	"Counting ranges......................................"	)
		{
		ostringstream os;
		boost::copy(
			boost::irange(1, 8),
		 	ostream_iterator<int>(os, "..")
		);
CK_compare(	os.str()	, "1..2..3..4..5..6..7.."		)
		}
		{
		ostringstream os;
		boost::copy(
			boost::irange(3, 32, 9),
		 	ostream_iterator<int>(os, "..")
		);
CK_compare(	os.str()	, "3..12..21.."			)
		}
		{
		ostringstream os;
		boost::copy(
			boost::irange(6, 2, -1),
		 	ostream_iterator<int>(os, "..")
		);
CK_compare(	os.str()	, "6..5..4..3.."			)
		}
		
}
