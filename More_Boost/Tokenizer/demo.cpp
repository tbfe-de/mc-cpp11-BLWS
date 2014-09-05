/*
 * Sum up integer values in a stringG
 * - values may be separates by either comma or semicolon
 * - values may be surrounded by spaces
 * - values may NOT be separated by white space only
*/

#include <string>
	using namespace std;

#include <boost/algorithm/string.hpp>
	using boost::trim_copy_if;
	using boost::is_any_of;
	
#include <boost/lexical_cast.hpp>
	using boost::lexical_cast;

#include <boost/tokenizer.hpp>
	using boost::tokenizer;
	using boost::char_separator;

int process(const string &s) {
	int sum= 0;
	char_separator<char> sep(",;");
	tokenizer<char_separator<char> > t(s, sep);
    	tokenizer<char_separator<char> >::iterator it= t.begin();
    	while (it != t.end())
       		sum+= lexical_cast<int>(
				trim_copy_if(*it++, is_any_of(" "))
			);
	return sum;
}

#include "Util/CK/CK.h"

int main() {

CK_section(	"Empty input ..................."	)
CK_compare(	process("")			, 0	)
CK_compare(	process(" ")			, 0	)

CK_section(	"One number ...................."	)
CK_compare(	process("1")			, 1	)
CK_compare(	process("2")			, 2	)
CK_compare(	process(" 3")			, 3	)
CK_compare(	process("4 ")			, 4	)
CK_compare(	process("  5 ")			, 5	)

CK_section(	"Two numbers ..................."	)
CK_compare(	process("1,2")			, 3	)
CK_compare(	process("1;2")			, 3	)
CK_compare(	process("1, 2")			, 3	)
CK_compare(	process("1  ,  2")		, 3	)
CK_compare(	process("  1    ,     2  ")	, 3	)

CK_section(	"Many numbers .................."	)
CK_compare(	process("1,2,3,4")		, 10	)
CK_compare(	process("1; 2; 3; 4")		, 10	)
CK_compare(	process("1 , 2 , 3 , 4")	, 10	)
CK_compare(	process("1,2,3,4,5,100,200")	, 315	)

}
