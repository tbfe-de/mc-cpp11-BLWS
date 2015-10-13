#ifndef MyRandom_H
#define MyRandom_H

#include <iterator>

class MyRandom
    : public std::iterator<std::input_iterator_tag, int> {
	const int lo, hi;
	int rnd;
	MyRandom(int lo_, int hi_, int rnd_)
		: lo(lo_), hi(hi_), rnd(rnd_) {}
public:
    MyRandom(int lo_ = 0, int hi_ = 1)
	: lo(lo_), hi(hi_) {
	operator()();
    }
    int operator*() const {
	return rnd;
    }
    int operator()() {
	return rnd = lo + std::rand() % (hi-lo+1);
    }
    MyRandom operator++() {
	operator()();
	return MyRandom(lo, hi, rnd);
    }
    MyRandom operator++(int) {
	const auto oldrnd = rnd;
	operator()();
	return MyRandom(lo, hi, oldrnd);
    }
};

#endif
