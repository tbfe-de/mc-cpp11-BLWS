#include <iostream>

#include <boost/logic/tribool.hpp>
	using boost::logic::tribool;
	using boost::logic::indeterminate;

int main() {
	using namespace std;

	tribool x(indeterminate);
	if (static_cast<bool>(x))
		cout << "static_cast<bool>(x)" << endl;
	if (x)
		cout << "implicit tribool -> bool conversion" << endl;
	if (!x)
		cout << "!x" << endl;
	if (!!x)
		cout << "!!x" << endl;
	if (!!!x)
		cout << "!!!x" << endl;
	if (x == x)
		cout << "x == x" << endl;
	if (x != x)
		cout << "x != x" << endl;
}
