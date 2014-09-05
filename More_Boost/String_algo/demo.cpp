/*
 * Demonstrate/test string algorithms from Boost.
*/

#include <boost/algorithm/string.hpp>
	using boost::trim_copy;
	using boost::trim_left_copy;
	using boost::trim_right_copy;

	using boost::trim_copy_if;
	using boost::trim_left_copy_if;
	using boost::trim_right_copy_if;

	using boost::to_upper_copy;
	using boost::to_lower_copy;

	using boost::replace_all_copy;
	using boost::replace_first_copy;
	using boost::replace_last_copy;

	using boost::erase_all_copy;
	using boost::erase_head_copy;
	using boost::erase_tail_copy;

	using boost::contains;
	using boost::icontains;
	using boost::starts_with;
	using boost::istarts_with;
	using boost::ends_with;
	using boost::iends_with;

	using boost::is_any_of;

#include <boost/algorithm/string/classification.hpp>
	using boost::is_upper;
	using boost::is_lower;
	using boost::is_alpha;
	using boost::is_digit;
	using boost::is_xdigit;
	using boost::is_alnum;

#include <string>
	using std::string;

#include "Util/CK/CK.h"

int main() {

CK_section(	"Trimming ......................"					)
CK_compare(	trim_copy(string(""))				, string("")		)
CK_compare(	trim_copy(string("abc"))			, string("abc")		)
CK_compare(	trim_copy(string("abc   "))			, string("abc")		)
CK_compare(	trim_copy(string("   abc"))			, string("abc")		)
CK_compare(	trim_copy(string("   abc   "))			, string("abc")		)
CK_compare(	trim_copy(string("\t\n  abc  \n\t"))		, string("abc")		)

CK_section(	"Trimming left ................."					)
CK_compare(	trim_left_copy(string(""))			, string("")		)
CK_compare(	trim_left_copy(string("abc"))			, string("abc")		)
CK_compare(	trim_left_copy(string("abc   "))		, string("abc   ")	)
CK_compare(	trim_left_copy(string("   abc"))		, string("abc")		)
CK_compare(	trim_left_copy(string("   abc   "))		, string("abc   ")	)
CK_compare(	trim_left_copy(string("\t\n  abc  \n\t"))	, string("abc  \n\t")	)

CK_section(	"Trimming right ................"					)
CK_compare(	trim_right_copy(string(""))			, string("")		)
CK_compare(	trim_right_copy(string("abc"))			, string("abc")		)
CK_compare(	trim_right_copy(string("abc   "))		, string("abc")		)
CK_compare(	trim_right_copy(string("   abc"))		, string("   abc")	)
CK_compare(	trim_right_copy(string("   abc   "))		, string("   abc")	)
CK_compare(	trim_right_copy(string("\t\n  abc  \n\t"))	, string("\t\n  abc")	)

CK_section(	"Trimming if ..................."					)
CK_compare(	trim_copy_if(string("abc"), is_any_of(""))		, string("abc")	)
CK_compare(	trim_copy_if(string("bcd"), is_any_of("a"))		, string("bcd")	)
CK_compare(	trim_copy_if(string("bcd"), is_any_of("ab"))		, string("cd")	)
CK_compare(	trim_copy_if(string("aabcd"), is_any_of("a"))		, string("bcd")	)
CK_compare(	trim_copy_if(string("aabcd"), is_any_of("ad"))		, string("bc")	)

CK_section(	"Trimming left if .............."					)
CK_compare(	trim_left_copy_if(string("abc"), is_any_of(""))		, string("abc")	)
CK_compare(	trim_left_copy_if(string("bcd"), is_any_of("a"))	, string("bcd")	)
CK_compare(	trim_left_copy_if(string("bcd"), is_any_of("ab"))	, string("cd")	)
CK_compare(	trim_left_copy_if(string("aabcd"), is_any_of("a"))	, string("bcd")	)
CK_compare(	trim_left_copy_if(string("aabcd"), is_any_of("ab"))	, string("cd")	)

CK_section(	"Trimming right if ............."					)
CK_compare(	trim_right_copy_if(string("abc"), is_any_of(""))	, string("abc")	)
CK_compare(	trim_right_copy_if(string("abc"), is_any_of("d"))	, string("abc")	)
CK_compare(	trim_right_copy_if(string("abc"), is_any_of("cd"))	, string("ab")	)
CK_compare(	trim_right_copy_if(string("abcdd"), is_any_of("d"))	, string("abc")	)
CK_compare(	trim_right_copy_if(string("abcdd"), is_any_of("cd"))	, string("ab")	)

CK_section(	"Erase all ....................."					)
CK_compare(	erase_all_copy(string("abcab"), "")		, string("abcab")	)
CK_compare(	erase_all_copy(string("abcab"), "a")		, string("bcb")		)
CK_compare(	erase_all_copy(string("abcab"), "b")		, string("aca")		)
CK_compare(	erase_all_copy(string("abcab"), "c")		, string("abab")	)
CK_compare(	erase_all_copy(string("abcab"), "ab")		, string("c")		)
CK_compare(	erase_all_copy(string("abcab"), "ef")		, string("abcab")	)

CK_section(	"Erase head....................."					)
CK_compare(	erase_head_copy(string("abcab"), 0)		, string("abcab")	)
CK_compare(	erase_head_copy(string("abcab"), 2)		, string("cab")		)
CK_compare(	erase_head_copy(string("abcab"), 3)		, string("ab")		)
CK_compare(	erase_head_copy(string("abcab"), 5)		, string("")		)
CK_compare(	erase_head_copy(string("abcab"), 8)		, string("")		)

CK_section(	"Erase tail....................."					)
CK_compare(	erase_tail_copy(string("abcab"), 0)		, string("abcab")	)
CK_compare(	erase_tail_copy(string("abcab"), 2)		, string("abc")		)
CK_compare(	erase_tail_copy(string("abcab"), 3)		, string("ab")		)
CK_compare(	erase_tail_copy(string("abcab"), 5)		, string("")		)
CK_compare(	erase_tail_copy(string("abcab"), 8)		, string("")		)

CK_section(	"Replace all ..................."					)
CK_compare(	replace_all_copy(string("abcab"), "", "xy")	, string("abcab")	)
CK_compare(	replace_all_copy(string("abcab"), "ab", "")	, string("c")	)
CK_compare(	replace_all_copy(string("abcab"), "ab", "xy")	, string("xycxy")	)
CK_compare(	replace_all_copy(string("abcab"), "ef", "xy")	, string("abcab")	)

CK_section(	"Replace first ................."					)
CK_compare(	replace_first_copy(string("abcab"), "", "xy")	, string("abcab")	)
CK_compare(	replace_first_copy(string("abcab"), "ab", "")	, string("cab")	)
CK_compare(	replace_first_copy(string("abcab"), "ab", "xy")	, string("xycab")	)
CK_compare(	replace_first_copy(string("abcab"), "ef", "xy")	, string("abcab")	)

CK_section(	"Replace last .................."					)
CK_compare(	replace_last_copy(string("abcab"), "", "xy")	, string("abcab")	)
CK_compare(	replace_last_copy(string("abcab"), "ab", "")	, string("abc")	)
CK_compare(	replace_last_copy(string("abcab"), "ab", "xy")	, string("abcxy")	)
CK_compare(	replace_last_copy(string("abcab"), "ef", "xy")	, string("abcab")	)

CK_section(	"Changing to upper case ........"					)
CK_compare(	to_upper_copy(string(""))		, string("")			)
CK_compare(	to_upper_copy(string("abc"))		, string("ABC")			)
CK_compare(	to_upper_copy(string("aBc"))		, string("ABC")			)
CK_compare(	to_upper_copy(string("ABC"))		, string("ABC")			)
CK_compare(	to_upper_copy(string("123"))		, string("123")			)
CK_compare(	to_upper_copy(string("abc-def"))	, string("ABC-DEF")		)
CK_compare(	to_upper_copy(string("Abc..xyz"))	, string("ABC..XYZ")		)
CK_compare(	to_upper_copy(string("Abc..xyz"))	, string("ABC..XYZ")		)

CK_section(	"Changing to lower case ........"					)
CK_compare(	to_lower_copy(string(""))		, string("")			)
CK_compare(	to_lower_copy(string("abc"))		, string("abc")			)
CK_compare(	to_lower_copy(string("aBc"))		, string("abc")			)
CK_compare(	to_lower_copy(string("ABC"))		, string("abc")			)
CK_compare(	to_lower_copy(string("123"))		, string("123")			)
CK_compare(	to_lower_copy(string("abc-def"))	, string("abc-def")		)
CK_compare(	to_lower_copy(string("Abc..xyz"))	, string("abc..xyz")		)
CK_compare(	to_lower_copy(string("Abc..xyz"))	, string("abc..xyz")		)

CK_section(	"Checking part ................."					)
CK_compare(	contains(string(""), "")		, true				)
CK_compare(	contains(string("abce"), "")		, true				)
CK_compare(	contains(string("abce"), "bc")		, true				)
CK_compare(	contains(string("aBce"), "bc")		, false				)
CK_compare(	contains(string("abce"), "cd")		, false				)

CK_section(	"Checking part (ignore case) .. "					)
CK_compare(	icontains(string(""), "")		, true				)
CK_compare(	icontains(string("abce"), "")		, true				)
CK_compare(	icontains(string("abce"), "bc")		, true				)
CK_compare(	icontains(string("aBce"), "bc")		, true				)
CK_compare(	icontains(string("abce"), "cd")		, false				)

CK_section(	"Checking start ................"					)
CK_compare(	starts_with(string(""), "")		, true				)
CK_compare(	starts_with(string("abcde"), "")	, true				)
CK_compare(	starts_with(string("abcde"), "ab")	, true				)
CK_compare(	starts_with(string("Abcde"), "ab")	, false				)
CK_compare(	starts_with(string("abcde"), "cd")	, false				)

CK_section(	"Checking start (ignore case) .."					)
CK_compare(	istarts_with(string(""), "")		, true				)
CK_compare(	istarts_with(string("abcde"), "")	, true				)
CK_compare(	istarts_with(string("abcde"), "ab")	, true				)
CK_compare(	istarts_with(string("Abcde"), "ab")	, true				)
CK_compare(	istarts_with(string("abcde"), "cd")	, false				)

CK_section(	"Checking end .................."					)
CK_compare(	ends_with(string(""), "")		, true				)
CK_compare(	ends_with(string("abcde"), "")		, true				)
CK_compare(	ends_with(string("abcde"), "de")	, true				)
CK_compare(	ends_with(string("abcdE"), "de")	, false				)
CK_compare(	ends_with(string("abcde"), "bc")	, false				)

CK_section(	"Checking end (ignore case) ...."					)
CK_compare(	iends_with(string(""), "")		, true				)
CK_compare(	iends_with(string("abcde"), "")		, true				)
CK_compare(	iends_with(string("abcde"), "de")	, true				)
CK_compare(	iends_with(string("abcdE"), "de")	, true				)
CK_compare(	iends_with(string("abcde"), "bc")	, false				)

CK_section(	"Checking for upper case ......."					)
CK_compare(	all(string(""), is_upper())		, true				)
CK_compare(	all(string("abc"), is_upper())		, false				)
CK_compare(	all(string("aBc"), is_upper())		, false				)
CK_compare(	all(string("ABC"), is_upper())		, true				)
CK_compare(	all(string("123"), is_upper())		, false				)

CK_section(	"Checking for lower case ......."					)
CK_compare(	all(string(""), is_lower())		, true				)
CK_compare(	all(string("abc"), is_lower())		, true				)
CK_compare(	all(string("aBc"), is_lower())		, false				)
CK_compare(	all(string("ABC"), is_lower())		, false				)
CK_compare(	all(string("123"), is_lower())		, false				)

CK_section(	"Checking for letters .........."					)
CK_compare(	all(string(""), is_alpha())		, true				)
CK_compare(	all(string("abc"), is_alpha())		, true				)
CK_compare(	all(string("aBc"), is_alpha())		, true				)
CK_compare(	all(string("ABC"), is_alpha())		, true				)
CK_compare(	all(string("123"), is_alpha())		, false				)

CK_section(	"Checking for digits ..........."					)
CK_compare(	all(string(""), is_digit())		, true				)
CK_compare(	all(string("abc"), is_digit())		, false				)
CK_compare(	all(string("aBc"), is_digit())		, false				)
CK_compare(	all(string("ABC"), is_digit())		, true				)
CK_compare(	all(string("123"), is_digit())		, true				)

CK_section(	"Checking combinations ........."					)
CK_compare(	all(string("a9c"), !is_digit())		, false				)
CK_compare(	all(string("a9c"), !is_lower())		, false				)
CK_compare(	all(string("a9c"), !is_upper())		, true				)
CK_compare(	all(string("a9c"), !is_digit())		, false				)
CK_compare(	all(string("rot"), is_lower()
				&& !is_xdigit())	, true				)
CK_compare(	all(string("blau"), is_lower()
				&& !is_xdigit())	, false				)

}

