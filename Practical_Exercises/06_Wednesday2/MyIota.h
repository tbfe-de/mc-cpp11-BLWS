#ifndef MyIota_H
#define MyIota_H

#include <iterator>

class MyIota
    : public std::iterator<std::input_iterator_tag, int> {
    int i, s;
public:
    MyIota(int i_ = 0, int s_ = 1)
	: i(i_), s(s_)
    {}
    int operator*() {
	return i;
    }
    int operator()() {
	return i += s;
    }
    MyIota operator++() {
	return MyIota(i += s, s);
    }
    MyIota operator++(int) {
	i += s;
	return MyIota(i - s, s);
    }
};

#endif
