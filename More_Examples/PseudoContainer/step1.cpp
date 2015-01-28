/*
 ======================================================================
 A "Pseudo-Container" of Prime Numbers with an Iterator Interface
 ======================================================================
 This version is rather a "proof oc concept" - it just implements what
 is necesarry to get a bare-bones program running.
*/
#include <cassert>
#include <iterator>
#include <vector>

class primes {
	std::vector<int> known;
	const int max;
	void calculate_next() {
		int candidate = known.back();
		for (;;) {
			candidate += 2;
			for (auto test : known) {
				if (candidate % test == 0)
					continue;
			}
			known.push_back(candidate);
			return;
		}
	}
	
public:
	primes(int m) : max(m) {
		known.push_back(2);
		known.push_back(3);
	}
	class iterator;
	iterator begin();
	iterator end();
	friend class iterator;
};

class primes::iterator
	: public std::iterator<std::input_iterator_tag, int> {
	int ith;
	primes &cont;
	friend class primes;
	iterator(primes &c, int i) : cont(c), ith(i) {}
public:
	int operator*() {
		if (ith >= cont.known.size())
			cont.calculate_next();
		return cont.known.at(ith);
	}
	iterator operator++() { 
		++ith;
		return *this;
	}
	friend bool operator!=(const primes::iterator &, const primes::iterator &);
	friend bool operator==(const primes::iterator &, const primes::iterator &);
};

primes::iterator primes::begin() {
	return iterator(*this, 0);
}

primes::iterator primes::end() {
	return iterator(*this, max);
}

bool operator!=(const primes::iterator& lhs, const primes::iterator &rhs) {
	return lhs.ith != rhs.ith;
}
bool operator==(const primes::iterator& lhs, const primes::iterator &rhs) {
	return lhs.ith == rhs.ith;
}

#include <iostream>

int main() {
	primes p10(10);
	for (auto p : p10)
		std::cout << p << ' ';
	std::cout << std::endl;
}
