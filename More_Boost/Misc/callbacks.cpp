#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
using namespace std;

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

template<typename Iterator, typename CodeBlock>
inline
void my_for_each(Iterator start, Iterator end, CodeBlock code) {
	while (start != end)
		code(*start++);
}

void printValueToCout(double d) {
	cout << "-> " << d << endl;
}

void printValue(ostream& os, double d) {
	os << ": " << d << endl;
}

struct SimplePrinter {
	void operator()(double d) const {
		cout << d << endl;
	}
};

struct NumberingPrinter {
	NumberingPrinter() : n(0) {}
	void operator()(double d, int dist = 1) {
		n += dist;
		cout << n << ": " << d << endl;
	}
private:
	int n;
};

int main() {
	vector<double> data;
	data.push_back(1.2);
	data.push_back(3.4);
	data.push_back(-0.5);
	data.push_back(6.7);
	boost::function<void (double)> printerToUse;
	int x = 5;
	switch(x) {
		case 1: printerToUse =
			SimplePrinter(); break;
		case 2: printerToUse =
			NumberingPrinter(); break;
		case 3: printerToUse =
			printValueToCout; break;
		case 4: printerToUse =
			boost::bind(printValue, boost::ref(cout), _1); break;
		case 5: printerToUse =
				[] (double v) { printValue(cout, v); }; break;
	}
	my_for_each(data.begin(), data.end(), printerToUse);
}
