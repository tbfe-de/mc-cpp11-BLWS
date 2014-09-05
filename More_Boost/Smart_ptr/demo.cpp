#include "Util/CK/CK.h"
#include "Util/CDCA_Tracer/CDCA_Tracer.h"

#include <memory>
using namespace std;

int main() {

CK_section(	"Shared pointer c'tors/d'tors ............."	)
	{
		shared_ptr<CDCA_Tracer> p0;
CK_compare(	CDCA_Tracer::getMessages()		,
			"" 				)
		shared_ptr<CDCA_Tracer> p1(new CDCA_Tracer());
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <1>"			"\n"	)
		{
			shared_ptr<CDCA_Tracer> p2(p1);
			shared_ptr<CDCA_Tracer> p3;
			p3= p2;
			p2.reset();
		}
CK_compare(	CDCA_Tracer::getMessages()		,
			"" 					)
	}
CK_compare(	CDCA_Tracer::getMessages()		,
			"deleted <1>"			"\n"	)

CK_section(	"Shared pointer target address ............"	)
	{
		CDCA_Tracer *const addr= new CDCA_Tracer();
		shared_ptr<CDCA_Tracer> p1(addr);
CK_compare(	p1.get()				, addr	)
		{
			shared_ptr<CDCA_Tracer> p2(p1);
CK_compare(		p2.get()			, addr	)
			shared_ptr<CDCA_Tracer> p3;
CK_compare(		p3.get()			, 0	)
			p3= p2;
CK_compare(		p3.get()			, addr	)
			p2.reset();
CK_compare(		p2.get()			, 0	)
		}
	}
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <2>"			"\n"
			"deleted <2>"			"\n"	)

CK_section(	"Shared pointer validity .................."	)
	{
		CDCA_Tracer *const addr= new CDCA_Tracer();
		shared_ptr<CDCA_Tracer> p1(addr);
CK_compare(	static_cast<bool>(p1)			, true	)
		{
			shared_ptr<CDCA_Tracer> p2(p1);
CK_compare(		static_cast<bool>(p2)		, true	)
			shared_ptr<CDCA_Tracer> p3;
CK_compare(		static_cast<bool>(p3)		, false	)
			p3= p2;
CK_compare(		static_cast<bool>(p3)		, true	)
			p2.reset();
CK_compare(		static_cast<bool>(p2)		, false	)
		}
	}
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <3>"			"\n"
			"deleted <3>"			"\n"	)

CK_section(	"Shared pointer unique ...................."	)
	{
		shared_ptr<CDCA_Tracer> p1(new CDCA_Tracer());
CK_compare(	p1.unique()				, true	)
		{
			shared_ptr<CDCA_Tracer> p2(p1);
CK_compare(		p1.unique()			, false	)
CK_compare(		p2.unique()			, false	)
			shared_ptr<CDCA_Tracer> p3;
CK_compare(		p3.unique()			, false	)
			p3= p2;
CK_compare(		p3.unique()			, false	)
			p2.reset();
CK_compare(		p2.unique()			, false	)
CK_compare(		p3.unique()			, false	)
		}
CK_compare(	p1.unique()				, true	)
	}
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <4>"			"\n"
			"deleted <4>"			"\n"	)

CK_section(	"Shared pointer use count ................."	)
	{
		shared_ptr<CDCA_Tracer> p1(new CDCA_Tracer());
CK_compare(	p1.use_count()				, 1	)
		{
			shared_ptr<CDCA_Tracer> p2(p1);
CK_compare(		p1.use_count()			, 2	)
CK_compare(		p2.use_count()			, 2	)
			shared_ptr<CDCA_Tracer> p3;
CK_compare(		p3.use_count()			, 0	)
			p3= p2;
CK_compare(		p3.use_count()			, 3	)
			p2.reset();
CK_compare(		p2.use_count()			, 0	)
CK_compare(		p3.use_count()			, 2	)
		}
CK_compare(	p1.use_count()				, 1	)
	}
CK_compare(	CDCA_Tracer::getMessages()		,
			"created <5>"			"\n"
			"deleted <5>"			"\n"	)

}

