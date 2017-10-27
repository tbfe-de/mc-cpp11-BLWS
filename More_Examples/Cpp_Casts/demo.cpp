void pessimize(void *, ...) {}

/*
 C++ Style Casts
 1. static_cast:
    - may be used for
      - conversions that would also happen automatically
        - to emphasize that a conversion takes place
        - to avoid compile warning
      - to revert conversions that take place only in
        one direction
        - integral to enum
        - void-pointer to typed pointer
        - Base -> Derived (= down-cast) EXCEPT in case
          of multiple inheritance and virtual Base classes
      - for class specific conversions marked `explicit`
        - single-argument constructors (since C++98)
        - type-cast operator (since C++11)
    - may NOT be used for changing `const` or `volatile
      - consider `const_cast` in this case
    - generates code in some applications but
      is only a compile-time operation in others
    - potentially USAFE when used for down-cast
      - prefer dynamic_cast for this
*/

class Other {};

class MyClass {
	mutable int z;
public:
	explicit MyClass(int) {}
	explicit operator Other() const { return Other(); }
	void m() const { ++z; }
};

void foo(MyClass arg) {}
void bar(Other arg) {}

void foo_static() {
    long a = 10; short b = static_cast<short>(a);
    pessimize(&a, &b);
                       a = static_cast<long>(b);
    pessimize(&a, &b);

    enum color {R, G, B};
    color c = G;  unsigned int d = G;
          c = static_cast<color>(d);
    pessimize(&c, &d);

    void *vp = static_cast<void*>(&a);
    long *lp = static_cast<long*>(vp);
    pessimize(&vp, &lp);

//    foo(333);
    foo(MyClass(333)); // Explicit Constructor Call
    foo(MyClass{333}); // same (since C++11)
    foo((MyClass)333); // C-Style Cast
    foo(static_cast<MyClass>(333)); // C++-Style Cast

    MyClass m(0);
//    bar(m);
    bar(Other(m));
    bar((Other)m);
    bar(static_cast<Other>(m));
    bar(m.operator Other());
}
 
 /*
 2. const_cast:
    - may NOT change the type as such but only
      - add `const` or `volatile`
      - remove `const` or `volatile`
    - GENERALLY implementation defined, in practice
      - may cause inconsistent view when modifying const locals
      - may even CRASH the process when modifying const globals
    - is ALWAYS only a compile-time operation
    - typical safe use to share implementation of `const`
      non-`const` member functions
 */

#include <iostream>

void  show(const int *p) {
	std::cout << *p << std::endl;
}

int main() {	
	const int x = 101;
	show(&x);
	++const_cast<int&>(x);
	show(&x);
	std::cout << x << std::endl;
}

/*

 3. dynamic_cast:
    - typical use to down-cast in class hierarchy connected
      by ineritance
    - requires RTTI switch on AND at least one virtual member
      function in the highest level class participating
    - compile error if classes not connected by inheritance
    - typically safe, but at runtime, if invalid, may
      - either return `nullptr`
      - or throw an exception
 
 4. reinterpret_cast
    - changes the "compiler view" of some memory region
    - may be VERY UNSAFE and not portable
    - typical safe use to specify prominent hardware
      addresses in device drivers as integral values
*/
      

