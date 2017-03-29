#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "MyRandom.h"

const int MIN = 1;
const int MAX = 6;
const std::size_t N = 30*1000*1000;
std::vector<int> data;

int main() {

	std::cout << "... filling array of "
		  << N << ", with random nums: " << std::flush;
//	------------------------------------------------------------
	std::copy_n(MyRandom(MIN, MAX), N, std::back_inserter(data));
//	------------------------------------------------------------

	const auto n = std::accumulate(data.begin(), data.end(), 0LL);
	const auto expect = N*(MIN + MAX)/2;
	std::cout << n
		  << ((98*n/100 <= expect
		    && expect <= 102*n/100) ? " (OK)" : " !?!")
		  << std::endl;
}
