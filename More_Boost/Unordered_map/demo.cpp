#include "Util/CK/CK.h"

#include <boost/unordered_map.hpp>

int main() {
		typedef boost::unordered_map<int, char> Container;
CK_section(	"Construction .................."		)
		Container s;
CK_compare(	s.empty()				, true	)
CK_compare(	s.size()				, 0	)
CK_compare(	s.count(1)				, 0	)
CK_compare(	s.count(2)				, 0	)
CK_compare(	s.count(3)				, 0	)

CK_section(	"Insertion and change .........."		)
		s.insert(std::make_pair(1, 'A'));
		s[2] = 'b';
CK_compare(	s.empty()				, false	)
CK_compare(	s.size()				, 2	)
CK_compare(	s.count(1)				, 1	)
CK_compare(	s[1]					, 'A'	)
		s[1]= 'a';
CK_compare(	s[1]					, 'a'	)
CK_compare(	s.count(2)				, 1	)
CK_compare(	s[2]					, 'b'	)
CK_compare(	s.count(3)				, 0	)

CK_section(	"Searching keys ................"		)
CK_compare(	s.find(2) == s.end()			, false	)
CK_compare(	s.find(3) == s.end()			, true	)
		Container::iterator f2= s.find(2);
CK_compare(	f2->first				, 2	)
CK_compare(	f2->second				, 'b'	)

CK_section(	"Checked insertion ............."		)
		std::pair<Container::iterator, bool> res;
		res= s.insert(std::make_pair(2, 'B'));
CK_compare(	s.count(2)				, 1	)
CK_compare(	res.first == f2				, true	)
CK_compare(	res.first->second			, 'b'	)
CK_compare(	res.second				, false	)
		res= s.insert(std::make_pair(3, 'c'));
CK_compare(	res.first == s.find(3)			, true	)
CK_compare(	res.first->first			, 3	)
CK_compare(	res.first->second			, 'c'	)
CK_compare(	res.second				, true	)

CK_section(	"Removal ......................."		)
CK_compare(	s.size()				, 3	)
		s.erase(f2);
CK_compare(	s.size()				, 2	)
CK_compare(	s.count(1)				, 1	)
CK_compare(	s.count(2)				, 0	)
CK_compare(	s.count(3)				, 1	)
		s.clear();
CK_compare(	s.size()				, 0	)
}
