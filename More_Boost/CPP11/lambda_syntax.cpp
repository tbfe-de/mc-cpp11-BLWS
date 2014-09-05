#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

void printValue(std::ostream& os, const double &value) {
	os << value << std::endl;
}

struct ValuePrinter {
	ValuePrinter(std::ostream& os_) : os(os_) {}
	void operator()(const double& value) {
		os << value << std::endl;
	}
private:
	std::ostream &os;
};

double multiplyFunction(double lhs, double rhs) {
	return lhs*rhs;
}

struct MultiplyFunctor {
	double operator()(double lhs, double rhs) {
		return lhs*rhs;
	}
};

void extremaFunction(double value, double& min, double& max) {
	if (value < min) {
		min = value;
	}
	else if (value > max) {
		max = value;
	}
}

struct ExtremaFunctor {
	ExtremaFunctor(double &min_, double &max_)
		: min(min_), max(max_)
	{}
	void operator()(double value) {
		if (value < min) {
			min = value;
		}
		else if (value > max) {
			max = value;
		}
	}
private:	
	double &min, &max;
};

#include "Util/CK/CK.h"

int main() {
		///////////////////////////////////////////////////
		std::vector<double> data = {
			1.2, 3.4, 5.6
		};
		///////////////////////////////////////////////////
CK_section(	"process container with function (and bind) .."	) {
		// ------------------------------------------------
		std::ostringstream expect;
		std::for_each(
			data.begin(), data.end(), std::bind(
				printValue,
				std::ref(expect),
				std::placeholders::_1
			)
		);
CK_compare(	expect.str(),	"1.2\n"
				"3.4\n"
				"5.6\n"				)
		// ------------------------------------------------
CK_compare(	std::accumulate(
			data.begin(), data.end(), 1.0,
			multiplyFunction
		)					, 22.848)
		// ------------------------------------------------
		double min = data.front(), max = data.front();
		std::for_each(
			data.begin()+1, data.end(), std::bind(
				extremaFunction,
		     	        std::placeholders::_1,
				std::ref(min), std::ref(max)
			)
		);
CK_compare(	min					, 1.2	)
CK_compare(	max					, 5.6 	);
		} /////////////////////////////////////////////////
CK_section(	"process container with functor ............. "	) {
		// ------------------------------------------------
		std::ostringstream expect;
		std::for_each(
			data.begin(), data.end(),
			ValuePrinter(expect)
		);
CK_compare(	expect.str(),	"1.2\n"
				"3.4\n"
				"5.6\n"				)
CK_compare(	std::accumulate(
			data.begin(), data.end(),
		        1.0, MultiplyFunctor()
		)					, 22.848)
		double min = data.front(), max = data.front();
		std::for_each(
			data.begin()+1, data.end(),
			ExtremaFunctor(min, max)
		);
CK_compare(	min					, 1.2	)
CK_compare(	max					, 5.6 	);
		} /////////////////////////////////////////////////
CK_section(	"process container with C++11 lambda  ........"	) {
		// ------------------------------------------------
		std::ostringstream expect;
		std::for_each(
			data.begin(), data.end(),
			[&expect] (const double &value) {
				expect << value << std::endl;
			}
		);
CK_compare(	expect.str(),	"1.2\n"
				"3.4\n"
				"5.6\n"				)
		// ------------------------------------------------
CK_compare(	std::accumulate(
			data.begin(), data.end(), 1.0,
			[] (double lhs, double rhs) {
				return lhs*rhs;
			}
		)				, 22.848)
		// ------------------------------------------------
		double min = data.front(), max = data.front();
		std::for_each(
			data.begin()+1, data.end(),
			[&min, &max](double value) {
				if (value < min) {
					min = value;
				}
				else if (value > max) {
					max = value;
				}
			}
		);
CK_compare(	min					, 1.2	)
CK_compare(	max					, 5.6 	);
		} /////////////////////////////////////////////////
}
