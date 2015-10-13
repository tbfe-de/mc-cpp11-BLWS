#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "MyRandom.h"

const std::size_t N = 5*1000*1000;

void timingFor(std::function<void()> todo) {
	namespace sc = std::chrono;
	auto start = sc::high_resolution_clock::now();
	todo();
	const auto realtime = sc::high_resolution_clock::now() - start;
	std::cout << sc::duration_cast<sc::milliseconds>(realtime).count()
		  << " msec" << std::endl;
}

int main() {

	std::cout << "=== filling containers with "
		  << N << " elements ===" << std::endl;

	timingFor([]() {
		MyRandom r(1, N);
		std::cout << "... overhead random number generator ...: " << std::flush;
		for (long long i = 0; i < N; ++i)
			static_cast<void>(r());
	});

	static std::vector<int> data1;
	timingFor([&data1]() {
		MyRandom r(1, N);
		std::cout << "STL vector (insert at back): " << std::flush;
		std::copy_n(r, N, std::back_inserter(data1));
	});

	static std::deque<int> data2;
	timingFor([&data2]() {
		MyRandom r(1, N);
		std::cout << "STL deque (insert at back): " << std::flush;
		std::copy_n(r, N, std::back_inserter(data2));
	});

	static std::deque<int> data3;
	timingFor([&data3]() {
		MyRandom r(1, N);
		std::cout << "STL deque (insert at front): " << std::flush;
		std::copy_n(r, N, std::front_inserter(data3));
	});

	static std::list<int> data4;
	timingFor([&data4]() {
		MyRandom r(1, N);
		std::cout << "STL list (insert at back): " << std::flush;
		std::copy_n(r, N, std::back_inserter(data4));
	});

	static std::list<int> data5;
	timingFor([&data5]() {
		MyRandom r(1, N);
		std::list<int> data;
		std::cout << "STL list (insert at front): " << std::flush;
		std::copy_n(r, N, std::front_inserter(data5));
	});

	static std::forward_list<int> data6;
	timingFor([&data6]() {
		MyRandom r(1, N);
		std::cout << "STL forward_list (insert at front): " << std::flush;
		std::copy_n(r, N, std::front_inserter(data6));
	});

	static std::array<int, N> data7;
	timingFor([&data7]() {
		MyRandom r(1, N);
		std::cout << "STL array fixed-size (assignment): " << std::flush;
		std::copy_n(r, N, data7.begin());
	});

	static int data8[N];
	timingFor([&data8]() {
		MyRandom r(1, N);
		std::cout << "C-style classic array (assignment): " << std::flush;
		std::copy_n(r, N, &data8[0]);
	});

	static std::vector<int> data9(N);
	timingFor([&data9]() {
		MyRandom r(1, N);
		std::cout << "STL vector right-sized (assignment): " << std::flush;
		std::copy_n(r, N, data9.begin());
	});

	static std::vector<int> data10;
	timingFor([&data10]() {
		data10.resize(N);
		MyRandom r(1, N);
		std::cout << "STL vector pre-sized (assignment): " << std::flush;
		std::copy_n(r, N, data10.begin());
	});

	static std::vector<int> data11;
	timingFor([&data11]() {
		data11.reserve(N);
		MyRandom r(1, N);
		std::cout << "STL vector pre-reserved (insert at back): " << std::flush;
		std::copy_n(r, N, std::back_inserter(data11));
	});

	static std::set<int> data12;
	timingFor([&data12]() {
		MyRandom r(1, N);
		std::cout << "STL set tree-based (some dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data12, data12.begin()));
	});

	static std::unordered_set<int> data13;
	timingFor([&data13]() {
		MyRandom r(1, N);
		std::cout << "STL set hash-based (some dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data13, data13.begin()));
	});

	static std::set<int> data14;
	timingFor([&data14]() {
		MyRandom r(1, N/10);
		std::cout << "STL set tree-based (many dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data14, data14.begin()));
	});

	static std::unordered_set<int> data15;
	timingFor([&data15]() {
		MyRandom r(1, N/10);
		std::cout << "STL set hash-based (many dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data15, data15.begin()));
	});

	static std::set<int> data16;
	timingFor([&data16]() {
		MyRandom r(1, 10*N);
		std::cout << "STL set tree-based (hardly dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data16, data16.begin()));
	});

	static std::unordered_set<int> data17;
	timingFor([&data17]() {
		MyRandom r(1, 10*N);
		std::cout << "STL set hash-based (hardly dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data17, data17.begin()));
	});

	static std::multiset<int> data18;
	timingFor([&data18]() {
		MyRandom r(1, N);
		std::cout << "STL multiset tree-based (some dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data18, data18.begin()));
	});

	static std::unordered_multiset<int> data19;
	timingFor([&data19]() {
		MyRandom r(1, N);
		std::cout << "STL multiset hash-based (some dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data19, data19.begin()));
	});

	static std::multiset<int> data20;
	timingFor([&data20]() {
		MyRandom r(1, N/10);
		std::cout << "STL multiset tree-based (many dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data20, data20.begin()));
	});

	static std::unordered_multiset<int> data21;
	timingFor([&data21]() {
		MyRandom r(1, N/10);
		std::cout << "STL multiset hash-based (many dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data21, data21.begin()));
	});

	static std::multiset<int> data22;
	timingFor([&data22]() {
		MyRandom r(1, 10*N);
		std::cout << "STL multiset tree-based (hardly dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data22, data22.begin()));
	});

	static std::unordered_multiset<int> data23;
	timingFor([&data23]() {
		MyRandom r(1, 10*N);
		std::cout << "STL multiset hash-based (hardly dups): " << std::flush;
		std::copy_n(r, N, std::inserter(data23, data23.begin()));
	});

	std::cout << "ALL DONE" << std::endl;

}
