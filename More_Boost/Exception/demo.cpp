#include <string>
#include <iostream>
using namespace std;

#include <boost/exception/all.hpp>

struct exception_base: virtual std::exception, virtual boost::exception {};
//struct exception_actually_thrown: virtual exception_base {};
//struct exception_finally_caught: virtual exception_actually_thrown {};

typedef boost::error_info<struct karl, double> level3_info;
typedef boost::error_info<struct hugo, string> level2_added_info;
typedef boost::error_info<struct otto, char> level1_added_info;

void level3(bool do_throw, double some_error_relevant_level_3_info) {
	// stuff that happpens ...
	// ... doesn't matter ...
	// ... but eventually fails
	if (do_throw) {
		boost::throw_exception(exception_base()
			<< level3_info(some_error_relevant_level_3_info));
	}
}

void level2(bool do_throw) {
	try {
		level3(do_throw, 123.456);
	}
	catch (boost::exception& e) {
		e << level2_added_info("this is from level 2");
		throw;
	}
}

void level1() {
	for (char c = '1'; c <= '9'; ++c) {
		try {
			level2(c == '3');
		}
		catch (boost::exception& e) {
			e << level1_added_info(c);
			throw;
		}
	}
}

int main() {
	try {
		level1();
	}
	catch (boost::exception& e) {
		cerr << boost::diagnostic_information(e) << endl;
	}
}

