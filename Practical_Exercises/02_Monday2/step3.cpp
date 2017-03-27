#include <iostream>
#include <functional>

template<typename T>
T* unwrap(T* p) { return p; }

template<typename T>
T* unwrap(std::reference_wrapper<T> *p) { &p->get(); }

template<typename T>
void f(T x) {
    unwrap(&x)->m();
}

#include <cassert>
#include <string>

class MyClass {
public:
    int x;
    void m() const {
        std::cout << "MyClass::m() const x =" << x << std::endl;
    }
    void m() {
        std::cout << "MyClass::m() ++x =" << ++x << std::endl;
    }
//  MyClass(const MyClass&) =delete;  // enable this for part (b) and (c)
//  MyClass(const MyClass&) =default; // for all other parts use this
};

int main() {
    MyClass obj{10};
    const MyClass cobj{1};
    f(obj); // disable this for part (b) and (c)
    f(cobj); // disable this for part (b) and (c)
    assert(obj.x == 10);
    assert(cobj.x == 1);

    f(std::cref(obj));
    f(std::cref(cobj));
    assert(cobj.x == 1);
    assert(obj.x == 10);
    assert(cobj.x == 1);

    f(std::ref(obj));
    f(std::ref(cobj));
    assert(obj.x == 11);
    assert(cobj.x == 1);
}
