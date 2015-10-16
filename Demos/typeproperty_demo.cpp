#include <type_traits>
#include <iostream>

template<typename Class1, typename Class2>
class C {
public:
    template<typename C1 = Class1, typename C2 = Class2>
    typename std::enable_if<!std::is_same<C1, C2>::value>::type
    m() {
         std::cout << "we need to do this in general\n";
    }
    template<typename C1 = Class1, typename C2 = Class2>
    typename std::enable_if<std::is_same<C1, C2>::value>::type
    m() {
         std::cout << "we need to do that if Class1 and Class2 are identical\n";
    }
};

class MyClass {};

int main() {
    C<MyClass, MyClass> obj3;
    obj3.m();
}
