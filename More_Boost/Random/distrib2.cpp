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

#include <boost/unordered_map.hpp>
	using boost::unordered_map;

#include <algorithm>
	using std::copy;
	using std::for_each;
	using std::generate_n;
#include <iostream>
	using std::cout;
	using std::endl;
	using std::ostream;
#include <iterator>
	using std::inserter;
#include <map>
	using std::map;

#define CNT (3000*1000LU)
typedef array<int, CNT> A;
A a;

// typedef unordered_multiset<int> M;
typedef map<int, int> M;

struct incr_me {
	incr_me(M &_theMap) : theMap(_theMap) {}
	void operator()(int idx) { ++theMap[idx]; }
private:
	M &theMap;
};

struct incr_me2 {
	incr_me2(M &_theMap) : theMap(_theMap) {}
	void operator()(std::pair<int, int> kv) { ++theMap[kv.second]; }
private:
	M &theMap;
};

struct print_me {
	print_me(ostream &_os) : os(_os) {}
	void operator()(const std::pair<int, int> &kv) {
		cout << format("%dx = %lu of %lu = %.5f %%\n")
				% kv.first
				% kv.second
				% CNT
				% (100.0 * kv.second / CNT);
	}
private:
	ostream &os;
};

int main() {

	mt19937 rng;
	variate_generator<mt19937&, uniform_int<> >
		 rn(rng, uniform_int<>(1, CNT));
	generate_n(a.begin(), CNT, rn);
	M m;
#if 0
	// explizite for-Schleife (geht immer)
	for(A::const_iterator it(a.begin()); it != a.end(); ++it)
		++m[*it];

	// for_each mit Boost.Lambda ...
	for_each(a.begin(), a.end(), ++m[_1]);
	// ... geht leider nicht, daher:
#endif
	// Work-Around mit functor
	for_each(a.begin(), a.end(), incr_me(m));

	M m2;
	m2[0]= CNT - m.size();
#if 0
	// explizite for-Schleife (geht immer)
	for(M::const_iterator it(m.begin()); it != m.end(); ++it)
		++m2[it->second];

	// for_each mit Boost.Lambda ...
	for_each(m.begin(), m.end(), ++m2[_1.second]);
	// ... geht leider nicht, daher:
#endif
	// Work-Around mit functor
	for_each(m.begin(), m.end(), incr_me2(m2));

#if 0
	// explizite for-Schleife (geht immer)
	for(M::const_iterator it(m2.begin()); it != m2.end(); ++it)
		cout << format("%dx = %lu of %lu = %.5f %%\n")
				% it->first
				% it->second
				% CNT
				% (100.0 * it->second / CNT);

	// for_each mit Boost.Lambda ...
	for_each(m2.begin(), m2.end(), 
		cout << format("%dx = %lu of %lu = %.5f %%\n")
				% _1.first
				% _1.second
				% CNT
				% (100.0 * _1.second / CNT));
	// ... geht leider nicht, daher:
#endif
	for_each(m2.begin(), m2.end(), print_me(cout));

}
