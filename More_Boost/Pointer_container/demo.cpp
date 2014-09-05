#include "Util/CK/CK.h"

#include <boost/ptr_container/ptr_vector.hpp>
	using boost::ptr_vector;
#include <boost/shared_ptr.hpp>
	using boost::shared_ptr;

#include "Util/CDCA_Tracer/CDCA_Tracer.h"

using namespace std;

int main() {

CK_section(	"Pointer container (vector) ..............."	) {
		ptr_vector<CDCA_Tracer> v;
CK_compare(	v.size()				, 0	)
		CDCA_Tracer *a[3];
		const int N= sizeof a / sizeof a[0];
		for (int i= 0; i < N; ++i) {
			v.push_back(a[i]= new CDCA_Tracer());
		}
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <1>"		"\n"
			"created <2>"		"\n"
			"created <3>"		"\n"	)
CK_compare(	v.size()			, 3	)
CK_compare(	&v.front()			, a[0]	)
CK_compare(	&v.back()			, a[2]	)
CK_compare(	typeid(v.back())		, typeid(CDCA_Tracer))
		v.pop_back();
CK_compare(	CDCA_Tracer::getMessages()	,
			"deleted <3>"		"\n"	)
CK_compare(	v.size()			, 2	)
	}
CK_compare(	CDCA_Tracer::getMessages()		,
			"deleted <1>"			"\n"
			"deleted <2>"			"\n"	)
}

