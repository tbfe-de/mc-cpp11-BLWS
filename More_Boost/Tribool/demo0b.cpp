#include <iostream>

#include <boost/logic/tribool.hpp>
	using boost::logic::tribool;
	using boost::logic::indeterminate;

int main() {
	using namespace std;

	tribool x(indeterminate);
		cout << "indeterminate(x)" << endl;
	if (indeterminate(!x))
		cout << "indeterminate(!x)" << endl;
	if (indeterminate(!!x))
		cout << "indeterminate(!!x)" << endl;
	if (indeterminate(!!!x))
		cout << "indeterminate(!!!x)" << endl;
	if (indeterminate(x == x))
		cout << "indeterminate(x == x)" << endl;
	if (indeterminate(x != x))
		cout << "indeterminate(x != x)" << endl;
}
