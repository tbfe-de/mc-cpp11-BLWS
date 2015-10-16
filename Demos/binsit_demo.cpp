#include <iterator>

template<typename T>
class my_back_insert_iterator
    : public std::iterator<std::output_iterator_tag, typename T::value_type> {
    T& container;
public:
    class deref_lhs;
    my_back_insert_iterator(T &container_)
        : container(container_) {}
    my_back_insert_iterator& operator++() {}
    deref_lhs operator*() const {
        return deref_lhs(*this);
    }
};

template<typename T>
class my_back_insert_iterator<T>::deref_lhs {
    const my_back_insert_iterator<T>& it;
public:
    deref_lhs(const my_back_insert_iterator<T>& it_)
        : it(it_) {}
    template<typename T1>
    deref_lhs& operator=(T1&& rhs) {
        it.container.emplace_back(rhs);
        return *this;
    }
};

template<typename T>
my_back_insert_iterator<T>
my_back_inserter(T &container) {
    return my_back_insert_iterator<T>(container);
}

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data;
//  std::generate_n(my_back_insert_iterator<vector<int>>(data), // where to store
    std::generate_n(my_back_inserter(data),                     // (or shorter)
                    7,                                          // number of elements
                    [val = 1]() mutable { return val *= 3; });  // how to generate
    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<int>(std::cout, "\n"));
}

