#include "Util/CK/CK.h"

#include <boost/unordered_set.hpp>

int main() {
		typedef boost::unordered_set<int> Container;
CK_section(	"Construction .................."		)
		Container s;
CK_compare(	s.empty()				, true	)
CK_compare(	s.size()				, 0	)
CK_compare(	s.count(1)				, 0	)
CK_compare(	s.count(2)				, 0	)
CK_compare(	s.count(3)				, 0	)

CK_section(	"Insertion (general) ..........."		)
		s.insert(1);
		s.insert(2);
CK_compare(	s.empty()				, false	)
CK_compare(	s.size()				, 2	)
CK_compare(	s.count(1)				, 1	)
CK_compare(	s.count(2)				, 1	)
CK_compare(	s.count(3)				, 0	)
CK_compare(	s.find(2) == s.end()			, false	)
CK_compare(	s.find(3) == s.end()			, true	)

CK_section(	"Insertion (details) ..........."		)
		Container::iterator f2= s.find(2);
CK_compare(	*f2					, 2	)
		std::pair<Container::iterator, bool> res;
		res= s.insert(2);
CK_compare(	s.count(2)				, 1	)
CK_compare(	res.first == f2				, true	)
CK_compare(	res.second				, false	)
		res= s.insert(3);
		Container::iterator f3= s.find(3);
CK_compare(	res.first == f3				, true	)
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
