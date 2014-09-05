#include <boost/date_time/gregorian/gregorian.hpp>
	using namespace boost::gregorian;

#include <sstream>
	using namespace std;

#include <Util/CK/CK.h>

int main() {

	{
CK_section(	"Time point basics ............."				)
		date d1(2008, 11, 10);
CK_compare(	d1				, date(2008, 11, 10)		)
CK_compare(	d1.year()			, greg_year(2008)		)
CK_compare(	d1.month()			, greg_month(11)		)
CK_compare(	d1.day()			, greg_day(10)			)

CK_section(	"Time point string conversions ."				)
		date d2(from_string("1972-12-11"));
CK_compare(	d2				, date(1972, 12, 11)		)
CK_compare(	to_simple_string(d2)		, string("1972-Dec-11")		)
CK_compare(	to_iso_string(d2)		, string("19721211")		)
CK_compare(	to_iso_extended_string(d2)	, string("1972-12-11")		)

CK_section(	"Time point I/O ................"				)
		date d3;
		istringstream is("2005-Mar-15");
		is >> d3;
CK_compare(	d3				, date(2005, 3, 15)		)
		ostringstream os;
		os << d1;
CK_compare(	os.str()			, string("2008-Nov-10")		)

CK_section(	"Time point comparisons ........"				)
		date d4(d1);
CK_compare(	d1 == d3			, false				)
CK_compare(	d1 == d4			, true				)
CK_compare(	d1 != d3			, true				)
CK_compare(	d1 != d4			, false				)
CK_compare(	d1 < d3				, false				)
CK_compare(	d1 < d4				, false				)
CK_compare(	d1 > d3				, true				)
CK_compare(	d1 > d4				, false				)
	}

	{
CK_section(	"Duration basics ..............."				)
		date_duration two_days(2);
		date_duration five_days(5);
		date_duration seven_days(7);
		date_duration one_week(weeks(1));
		date_duration two_weeks(weeks(2));
CK_compare(	two_days			, date_duration(2)		)
CK_compare(	five_days			, date_duration(5)		)
CK_compare(	seven_days			, date_duration(7)		)
CK_compare(	seven_days			, weeks(1)			)
CK_compare(	one_week			, date_duration(7)		)
CK_compare(	two_weeks			, date_duration(14)		)

CK_section(	"Duration arithmetic ..........."				)
CK_compare(	two_days + five_days		, date_duration(7)		)
CK_compare(	one_week + five_days		, date_duration(12)		)
CK_compare(	one_week - five_days		, date_duration(2)		)
CK_compare(	one_week + one_week		, weeks(2)			)
CK_compare(	two_days + five_days + one_week	, weeks(2)			)

CK_section(	"Duration comparisons .........."				)
CK_compare(	two_days == five_days		, false				)
CK_compare(	two_days != five_days		, true				)
CK_compare(	two_days < five_days		, true				)
CK_compare(	two_days > five_days		, false				)
CK_compare(	seven_days == one_week		, true				)
	}

	{
CK_section(	"Date period basics ............"				)
		date_period p1(date(2008, 12, 5),
			       date(2008, 12, 7));
CK_compare(	p1.length()			, days(2)			)
CK_compare(	p1.contains(date(2008, 12, 4))	, false				)
CK_compare(	p1.contains(date(2008, 12, 5))	, true				)
CK_compare(	p1.contains(date(2008, 12, 6))	, true				)
CK_compare(	p1.contains(date(2008, 12, 7))	, false				)
CK_compare(	p1.contains(date(2008, 12, 8))	, false				)
CK_compare(	p1.contains(date(2012, 12, 5))	, false				)
CK_compare(	p1.is_before(date(2012, 12, 5))	, true				)
CK_compare(	p1.is_after(date(2012, 12, 5))	, false				)

CK_section(	"Date period comparisons ......."				)
		date_period p2(date(2008, 12, 5),
			       date(2008, 12, 6));
		date_period p3(date(2008, 12, 6),
			       date(2008, 12, 9));
		date_period p4(date(2012, 11, 1),
			       date(2012, 11, 5));
CK_compare(	p1.contains(p2)			, true				)
CK_compare(	p1.contains(p3)			, false				)
CK_compare(	p1.contains(p4)			, false				)
CK_compare(	p1.intersects(p2)		, true				)
CK_compare(	p1.intersects(p3)		, true				)
CK_compare(	p1.intersects(p4)		, false				)
CK_compare(	p4.is_adjacent(p1)		, false				)
CK_compare(	p2.is_adjacent(p3)		, true				)


CK_section(	"Date period other operations .."				)
CK_compare(	p1.intersection(p3)	, date_period(date(2008, 12, 6),
						      date(2008, 12, 7))	)
CK_compare(	p1.merge(p3)		, date_period(date(2008, 12, 5),
						      date(2008, 12, 9))	)
CK_compare(	p1.span(p4)		, date_period(date(2008, 12, 5),
						      date(2012, 11, 5))	)
		p1.shift(days(30));
CK_compare(	p1			, date_period(date(2009, 1, 4),
						      date(2009, 1, 6))		)
	}
}
