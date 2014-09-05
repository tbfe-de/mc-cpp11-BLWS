#include <boost/numeric/conversion/cast.hpp>

int main() {
	try {
		boost::numeric_cast<short>(7000L);
		return 0;
	}
	catch (...) {
		return 1;
	}
}
