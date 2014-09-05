#include <boost/array.hpp>
	using boost::array;

#include <boost/format.hpp>
	using boost::format;

#include <boost/lambda/lambda.hpp>
	using boost::lambda::_1;

#include <boost/random.hpp>
	using boost::mt19937;
	using boost::uniform_int;
	using boost::variate_generator;

#include <boost/unordered_set.hpp>
	using boost::unordered_set;

#include <algorithm>
	using std::copy;
	using std::for_each;
	using std::generate_n;
#include <iostream>
	using std::cout;
	using std::endl;
#include <iterator>
	using std::inserter;
#include <set>
	using std::set;

#define CNT (3000*1000LU)
array<int, CNT> data;

// typedef unordered_set<int> M;
typedef set<int> M;

int main() {


	mt19937 rng;
	variate_generator<mt19937&, uniform_int<> >
		 rn(rng, uniform_int<>(1, CNT));

	generate_n(data.begin(), CNT, rn);
	M m;
	copy(data.begin(), data.end(), inserter(m, m.begin()));
	
	cout << format("%lu of %lu = %.5f %%\n")
			% (CNT - m.size())
			% CNT
			% (100.0 * (static_cast<double>(CNT - m.size()) / CNT));

}
