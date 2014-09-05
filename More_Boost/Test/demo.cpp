#include <iostream>
#include <sstream>
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(allways_success) {
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(hello_world) {
	std::ostringstream os;
	os << "hello, world" << std::endl;
	BOOST_CHECK_EQUAL(os.str() , "hello, world\n");
}

int fakul(int n) {
	return (n > 0) ? n*fakul(n-1) : 1;
}

BOOST_AUTO_TEST_CASE(fakul_test) {
	BOOST_CHECK_EQUAL( fakul(0) , 1 );
	BOOST_CHECK_EQUAL( fakul(1) , 1 );
	BOOST_CHECK_EQUAL( fakul(2) , 2 );
	BOOST_CHECK_EQUAL( fakul(3) , 6 );
	BOOST_CHECK_EQUAL( fakul(4) , 24 );
	BOOST_CHECK_EQUAL( fakul(5) , 120 );
	BOOST_CHECK_EQUAL( fakul(6) , 720 );
	BOOST_CHECK_EQUAL( fakul(7) , 5040 );
	BOOST_CHECK_EQUAL( fakul(8) , 40320 );
	BOOST_CHECK_EQUAL( fakul(9) , 362880 );
	BOOST_CHECK_EQUAL( fakul(10) , 3628800 );
}
