#include <iostream>

class Value {
    int v;
public:
    Value(int v_) : v(v_) {}
    int get() const { return v; }
    Value& operator++() { ++v; return *this; }
    Value operator++(int) { int old = v; ++v; return Value(old); }
};

int main() {
Value x(42);
    std::cout << (x++).get() << '\n';
    int a = (++x).get();
    std::cout << a << '\n';
}
