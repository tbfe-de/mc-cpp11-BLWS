#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

#include "boost/multi_array.hpp"
#include "boost/range.hpp"
using boost::iterator_range;
using boost::make_iterator_range;

#include "boost/range/algorithm/copy.hpp"

template<class T>
void printline(const char* const text, T r) {
	cout << text;
	copy(make_iterator_range(r), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main() {
	// Create a 2D array type
	typedef boost::multi_array<int, 2> Matrix;

	Matrix data(boost::extents[4][2]);
	Matrix::array_view<1>::type column0 =
		data[boost::indices[boost::multi_array_types::index_range(0,3)][0]];
	Matrix::array_view<1>::type column1 =
		data[boost::indices[boost::multi_array_types::index_range(0,3)][1]];
	Matrix::array_view<1>::type row2 =
		data[boost::indices[2][boost::multi_array_types::index_range(0,2)]];

	cout << "Anzahl der Dimensionen: " << data.dimensionality << endl;
	printline("Elemente pro Dimension: ", make_iterator_range(data.shape(),
					      data.shape()+data.dimensionality));
	int n = 0;
	data[0][0] = ++n;
	data[0][1] = ++n;
	data[1][0] = ++n;
	data[1][1] = ++n;
	data[2][0] = ++n;
	data[2][1] = ++n;
	data[3][0] = ++n;
	data[3][1] = ++n;

	printline("erste Spalte: ", column0);
	printline("zweite Spalte: ", column1);
	printline("dritte Zeile: ", row2);
}
