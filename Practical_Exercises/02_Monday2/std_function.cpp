#include <cstdlib>
#include <iostream>
#include <functional>

void bar() { }
int baz() { return 123; }
int foo(char *cp) { *cp = 'H';  return 0; }

std::function<void(const char *)> f1 = std::atoi;
// std::function<int()> f2 = bar;
std::function<int()> f2 = baz;
std::function<int(char *)> f3 = foo;


int main() {
	int x = std::atoi("123");
//	int y = f1("123");
	int z = f2();
	const char text[] = "hello, world";
	f3(const_cast<char *>(text));

}
