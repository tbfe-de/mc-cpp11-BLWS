template <int v>
struct pwrof2 {
	static const bool value = ((v & 1u) == 0) && pwrof2<(v >> 1)>::value;
};

template<>
struct pwrof2<2> {
	static const bool value = true;
};

template<>
struct pwrof2<1> {
	static const bool value = false;
};

template<>
struct pwrof2<0> {
	static const bool value = false;
};

#include <iostream>
int main() {
	std::cout.setf(std::ios::boolalpha);
	std::cout << pwrof2<5>::value << std::endl;
}
