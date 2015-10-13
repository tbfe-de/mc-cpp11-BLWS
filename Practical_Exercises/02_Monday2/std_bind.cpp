#include <cmath>
#include <cstdlib>
#include <iostream>
#include <functional>

using namespace std::placeholders;
void baz(const char *a, int b) {
	std::cout << "a=" << a << std::endl;
	std::cout << "b=" << b << std::endl;
}
void bar(int x, double y, const char *z) {
	std::cout << "x=" << x << std::endl;
	std::cout << "y=" << y << std::endl;
	std::cout << "z=" << z << std::endl;
}

void foo(std::function<void(int, const char *)> f) {
	f(123, "hello");
}

int main() {
	bar(111, 3.14, "hi!");
	std::cout << "------" << std::endl;
	// foo(bar);
	foo(std::bind(bar, _1, std::sqrt(2.0), _2));
	std::cout << "------" << std::endl;
	// foo(baz);
	foo(std::bind(baz, _2, _1));
	std::cout << "------" << std::endl;
	foo(std::bind(baz, _2, 42));
	std::cout << "------" << std::endl;
	foo(std::bind(baz, "xxxx", _1));

}
