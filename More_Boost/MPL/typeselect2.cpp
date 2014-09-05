#include <iostream>

enum day { MON, TUE, WED, THU, FRI, SAT, SUN };

struct workday {
	static void doIt() {
		std::cout << "working nine to five" << std::endl;
	}
};

struct weekend {
	static void doIt() {
		std::cout << "stay at home" << std::endl;
	}
};

template<bool tf, class T1, class T2>
struct select2;

template<class T1, class T2>
struct select2<true, T1, T2> {
	typedef T1 result;
};

template<class T1, class T2>
struct select2<false, T1, T2> {
	typedef T2 result;
};

#define T WED

int main() {
	const day today = T;
	select2<today != SAT && today != SUN,
		workday,
		weekend
	>::result::doIt();
}
