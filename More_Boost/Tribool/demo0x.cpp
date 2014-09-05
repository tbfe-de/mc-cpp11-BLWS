#include <iostream>

#include <boost/logic/tribool.hpp>
	using boost::logic::tribool;
	using boost::logic::indeterminate;

int main() {
	using namespace std;

	if (static_cast<bool>(indeterminate))
		cout << "static_cast<bool>(indeterminate)" << endl;
	if (indeterminate)
		cout << "function pointer -> bool conversion" << endl;
	if (tribool())
		cout << "tribool default c'tor-> bool conversion" << endl;
	if (tribool(indeterminate))
		cout << "tribool(indeterminate) c'tor-> bool conversion" << endl;
	if (!indeterminate)
		cout << "!indeterminate" << endl;
	if (!!indeterminate)
		cout << "!!indeterminate" << endl;
	if (!!!indeterminate)
		cout << "!!!indeterminate" << endl;
	if (indeterminate == indeterminate)
		cout << "indeterminate == indeterminate" << endl;
	if (indeterminate != indeterminate)
		cout << "indeterminate != indeterminate" << endl;
}
