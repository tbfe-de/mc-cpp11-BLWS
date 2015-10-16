template<typename T>
class TypePrint;

template<typename BaseType>
struct add_pointer {
    typedef BaseType* type;
};

template<typename>
struct remove_ptr;

template<typename BaseType>
struct remove_ptr<BaseType*> {
     typedef BaseType type;
};

TypePrint<remove_ptr<int*>::type> x;
TypePrint<remove_ptr<double***>::type> y;

int main() {}
