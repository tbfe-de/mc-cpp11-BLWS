#include <iostream>

enum day { MON, TUE, WED, THU, FRI, SAT, SUN };

template<bool b>
struct workday_weekend;

template<>
struct workday_weekend<true> {
	static void doIt() {
		std::cout << "working nine to five" << std::endl;
	}
};

template<>
struct workday_weekend<false> {
	static void doIt() {
		std::cout << "stay at home" << std::endl;
	}
};

#define T WED

int main() {
	const day today = T;
	workday_weekend<today != SAT && today != SUN>::doIt();
}
