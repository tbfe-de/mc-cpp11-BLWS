#include <type_traits>
#include <utility>

#if 0
#if 0
template<class CT,
         class VT = typename CT::value_type,
         class = decltype(std::declval<CT>().push_back(std::declval<VT>()))>
std::true_type  has_push_back_test(const CT&);
std::false_type has_push_back_test(...);
template<class T>
using has_push_back = decltype(has_push_back_test(std::declval<T>()));

template<class CT,
         class VT = typename CT::value_type,
         class = decltype(std::declval<CT>().insert(std::declval<VT>()))> 
std::true_type has_insert_test();
std::false_type has_insert_test(...);
template<class T>
using has_insert = decltype(has_insert_test<T>());

#else

template<typename T> struct has_push_back {
    template<typename C, typename VT = typename C::value_type>
    static constexpr
    decltype((std::declval<C>().push_back(std::declval<VT>()), bool())) test(int) { return true; }
    template<typename C>
    static constexpr bool test(...) { return false; }
    static constexpr bool value = test<T>(0);
};

template<typename T> struct has_insert { 
    template<typename C, class VT = typename C::value_type>
    static constexpr
    decltype((std::declval<C>().insert(std::declval<VT>()), bool())) test(int) { return true; }    
    template<typename C>
    static constexpr bool test(...) { return false; }
    static constexpr bool value = test<T>(0);
};

#endif

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> std::enable_if_t<has_push_back<ContainerType>::value> {
    container.push_back(element);
    std::cout << "added " << element << " using push_back\n";
}

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> std::enable_if_t<has_insert<ContainerType>::value> {
    container.insert(element);
    std::cout << "added " << element << " using insert\n";
}

#else

template<typename CT,
         typename VT = typename CT::value_type,
         typename = decltype(std::declval<CT>().push_back(std::declval<VT>()))>
void has_push_back(const CT&);

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> decltype(has_push_back(container)) {
    container.push_back(element);
    std::cout << "added " << element << " using push_back\n";
}

template<typename CT,
         typename VT = typename CT::value_type,
         typename = decltype(std::declval<CT>().insert(std::declval<VT>()))>
void has_insert(const CT&);

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> decltype(has_insert(container)) {
    container.insert(element);
    std::cout << "added " << element << " using insert\n";
}

#endif

#include <string>
#include <vector>
#include <list>
#include <set>

int main()
{
    std::vector<double> x;      add_one(x, 5.67);
    std::set<int> y;            add_one(y, 1234);
    std::list<std::string> z;   add_one(z, "abc");
}
