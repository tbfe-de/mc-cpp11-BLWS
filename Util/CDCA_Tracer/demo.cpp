#include "CK.h"

#include "CDCA_Tracer.h"

using namespace std;

int main() {

CK_section(	"CDCA_Tracer sanity ......................."	)

	{ // <--BEGIN LOCAL SCOPE-->
		CDCA_Tracer first;
		{
			CDCA_Tracer second(first);
			CDCA_Tracer third;
			third= second;
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <1>"			"\n"
			"created <2> from <1>"		"\n"
			"created <3>"			"\n"
			"copied <3> from <2>"		"\n"	)
		}
CK_compare(	CDCA_Tracer::getMessages()		,
			"deleted <3>"			"\n"
			"deleted <2>"			"\n"	)
	} // <--END LOCAL SCOPE-->

CK_compare(	CDCA_Tracer::getMessages()		,
			"deleted <1>"			"\n"	)

}

