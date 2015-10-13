// Various ways to define a non-copyable (non-movable) class:

class MyClass0 {
    // defaults for move and copy created
public:
    MyClass0() {}
};

class MyClass1 {
    // classic style with private operations
    MyClass1(const MyClass1 &);
    MyClass1 &operator=(const MyClass1 &);
public:
    MyClass1() {}
};

#include <boost/noncopyable.hpp>
// with boost::noncopyable as base class
class MyClass2 : boost::noncopyable {
public:
    MyClass2() {}
};

class MyClass3 {
    // default copyable and default movable
public:
    MyClass3(const MyClass3 &)            = default;
    MyClass3& operator=(const MyClass3 &) = default;

    MyClass3(MyClass3 &&)                 = default;
    MyClass3& operator=(MyClass3 &&)      = default;
    MyClass3() {}
};

class MyClass4 {
    // default copyable, not movable
public:
    MyClass4(const MyClass4 &)            = default;
    MyClass4& operator=(const MyClass4 &) = default;

    MyClass4(MyClass4 &&)                 = delete;
    MyClass4& operator=(MyClass4 &&)      = delete;
    MyClass4() {}
};

class MyClass5 {
    // not copyable and default movable
public:
    MyClass5(const MyClass5 &)            = delete;
    MyClass5& operator=(const MyClass5 &) = delete;

    MyClass5(MyClass5 &&)                 = default;
    MyClass5& operator=(MyClass5 &&)      = default;
    MyClass5() {}
};

class MyClass6 {
    // not copyable and not movable
public:
    MyClass6(const MyClass6 &)            = delete;
    MyClass6& operator=(const MyClass6 &) = delete;

    MyClass6(MyClass6 &&)                 = delete;
    MyClass6& operator=(MyClass6 &&)      = delete;
    MyClass6() {}
};

// Test-Code

typedef MyClass3 MyClass;

// Request copy and move versions of constructor and assigmnent
// explcitely, so all of the below will work.

MyClass foo() {
    return MyClass();
}

int main() {
    MyClass a;
    MyClass b(a);
    a = b;
    MyClass c(foo());
    a = foo();
}
