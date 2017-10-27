
#include <iostream>
#include <type_traits>
#include <utility>

#if 0
template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> decltype(container.push_back(element)) {
    std::cout << "added " << element << " using push_back\n";
    return container.push_back(element);
}

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> decltype(container.insert(element)) {
    std::cout << "added " << element << " using insert\n";
    return container.insert(element);
}

#else

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> decltype(container.push_back(element), void()) {
    container.push_back(element);
    std::cout << "added " << element << " using push_back\n";
}

template<typename ContainerType, typename ElementType>
auto add_one(ContainerType &container, const ElementType& element)
-> decltype(container.insert(element), void()) {
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
