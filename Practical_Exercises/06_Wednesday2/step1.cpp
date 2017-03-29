#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "MyIota.h"
#include "MyRandom.h"

const std::size_t N = 1000;
std::array<int, N> data;

int main() {

	std::cout << "... filling array of "
		  << N << ", all same: " << std::flush;
	const int fixval = 7;
//	------------------------------------
	std::fill_n(data.begin(), N, fixval);
//	------------------------------------
	const auto n1 = std::accumulate(data.begin(), data.end(), 0LL);
	const auto expect1 = N*fixval;
	std::cout << n1
		  << ((n1 == expect1) ? " (OK)" : " !?!")
		  << std::endl;

	std::cout << "... filling array of "
		  << N << ", ascending: " << std::flush;
	const int first = 3;
//      -------------------------------------------
	std::iota(data.begin(), data.end(), first);
//      -------------------------------------------
	const auto n2 = std::accumulate(data.begin(), data.end(), 0LL);
	const auto expect2 = N*first + N*(N-1)/2;
	std::cout << n2
		  << ((n2 == expect2) ? " (OK)" : " !?!")
		  << std::endl;

	std::cout << "... filling array of "
		  << N << ", stepping up: "
		  << std::flush;
	const int initial = 0;
	const int increment = 5;
//      ------------------------------------------------------------
	std::generate_n(data.begin(), N, MyIota(initial, increment));
//      ------------------------------------------------------------
	const auto n3 = std::accumulate(data.begin(), data.end(), 0LL);
	const auto expect3 = N*initial + N*(N+1)/2*increment;
	std::cout << n3
		  << ((n3 == expect3) ? " (OK)" : " !?!")
		  << std::endl;

	std::cout << "... filling array of "
		  << N << ", with random nums: " << std::flush;
	const int low = 1;
	const int high = 6;
//      -----------------------------------------------------
	std::generate_n(data.begin(), N, MyRandom(low, high));
//      -----------------------------------------------------
	const auto n4 = std::accumulate(data.begin(), data.end(), 0LL);
	const auto expect4 = N*(low + high)/2;
	std::cout << n4
		  << ((n4*9/10 <= expect4
		    && expect4 <= n4*11/10) ? " (OK)" : " !?!")
		  << std::endl;
}
