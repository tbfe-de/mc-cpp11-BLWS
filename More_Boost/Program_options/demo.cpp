/* Exercise: Program_options/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for 'Boost.Program_options'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2012): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
*/
#define	X_SOLVED    5	/*?#*/

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Standard Library
#include <iostream>
	using std::cout;
	using std::endl;
	using std::ostream;
#include <sstream>
	using std::ostringstream;
#include <string>
	using std::string;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                        Boost.Program_options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                          Expectation Checker
#include "Util/CK/CK.h"

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//		                                                	 Step 1
// Add expected results for '?'.
//
#if X_SOLVED >= 1
namespace boost_workshop { namespace program_options { namespace step_1 {

void tests() {
		po::options_description desc("Allowed Options");

CK_section(	"(Empty) options description ................................."	)
		ostringstream out;
		out << desc;
				//////////////////////////////////
CK_compare(	out.str(),	"Allowed Options:\n"		       /*?:-1*/	)
				//////////////////////////////////

CK_section(	"Supply (unknown) options ...................................."	)
		po::variables_map vm;
		bool has_unknown_options = false;
		try {
			static const char* const ARGV[] = {
				"progname", "--verbose", "--delim=,"
			};
			static const int ARGC = (sizeof ARGV / sizeof ARGV[0]);
			po::store(po::parse_command_line(ARGC, ARGV, desc), vm);
		}
		catch (po::unknown_option &ex) {
			has_unknown_options = true;
		}
		//////////////////////////////////
CK_compare(	has_unknown_options,	true			       /*?:-1*/	)
CK_compare(	vm.count("verbose"),	0			       /*?:-1*/	)
CK_compare(	vm.count("delim"),	0			       /*?:-1*/	)
		//////////////////////////////////
}

}}} // EONS ::boost_workshop::program_options::step_1
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//		                                                	 Step 2
// Add expected results for '?'.
//
#if X_SOLVED >= 2
namespace boost_workshop { namespace program_options { namespace step_2 {

void tests() {
		po::options_description desc("Allowed Options");
		desc.add_options()
			( "verbose" ,                    "more verbose output"	)
			( "delim"   , po::value<char>(), "delimiter character"	)
		;

CK_section(	"Options description ........................................."	)
		ostringstream out;
		out << desc;
CK_compare(	out.str(),
			//////////////////////////////////////////////
			"Allowed Options:\n"
			"  --verbose             more verbose output\n"
			"  --delim arg           delimiter character\n"		)
			//////////////////////////////////////////////

CK_section(	"Supply both options ........................................."	)
		po::variables_map vm;
		bool has_unknown_options = false;
		try {
			static const char* const ARGV[] = {
				"progname", "--verbose", "--delim=,"
			};
			static const int ARGC = (sizeof ARGV / sizeof ARGV[0]);
			po::store(po::parse_command_line(ARGC, ARGV, desc), vm);
		}
		catch (po::unknown_option &ex) {
			has_unknown_options = true;
		}
				//////////////////////////////////
CK_compare(	has_unknown_options,	false			/*?:-1*/	)
CK_compare(	vm.count("verbose"),	1			/*?:-1*/	)
CK_compare(	vm.count("delim"),	1			/*?:-1*/	)
CK_compare(	vm["delim"].as<char>(),	','			/*?:-1*/	)
				//////////////////////////////////
CK_section(	"Supply single (valid) option ................................"	)
		has_unknown_options = false;
		//vm.clear();
		vm = po::variables_map();
		try {
			static const char* const ARGV[] = {
				"progname", "--verbose"
			};
			static const int ARGC = (sizeof ARGV / sizeof ARGV[0]);
			po::store(po::parse_command_line(ARGC, ARGV, desc), vm);
		}
		catch (po::unknown_option &ex) {
			has_unknown_options = true;
		}
				//////////////////////////////////
CK_compare(	has_unknown_options,	false			/*?:-1*/	)
CK_compare(	vm.count("verbose"),	1			/*?:-1*/	)
CK_compare(	vm.count("delim"),	0			/*?:-1*/	)
				//////////////////////////////////

CK_section(	"Supply single (valid) option twice .........................."	)
		has_unknown_options = false;
		vm.clear();
		vm = po::variables_map();
		try {
			static const char* const ARGV[] = {
				"progname", "--verbose", "--verbose"
			};
			static const int ARGC = (sizeof ARGV / sizeof ARGV[0]);
			po::store(po::parse_command_line(ARGC, ARGV, desc), vm);
		}
		catch (po::unknown_option &ex) {
			has_unknown_options = true;
		}
				//////////////////////////////////
CK_compare(	has_unknown_options,	false			/*?:-1*/	)
CK_compare(	vm.count("verbose"),	1			/*?:-1*/	)
CK_compare(	vm.count("delim"),	0			/*?:-1*/	)
				//////////////////////////////////
}

}}} // EONS ::boost_workshop::program_options::step_2
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// 				   Call tests - nothing to change from here on.
//
int main() {
#if X_SOLVED >= 1
	boost_workshop::program_options::step_1::tests();
#endif
#if X_SOLVED >= 2
	boost_workshop::program_options::step_2::tests();
#endif
}
