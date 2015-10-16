#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

template<typename T>
class my_ostream_iterator
    : public std::iterator<std::output_iterator_tag, T> {
    std::ostream &os;
    const std::string &sep;
public:
    class deref_lhs;
    my_ostream_iterator(std::ostream& os_,
                        const std::string& sep_ = std::string())
        : os(os_), sep(sep_) {}
    my_ostream_iterator& operator++() {}
    deref_lhs operator*() const {
        return deref_lhs(*this);
    }
};

template<typename T>
class my_ostream_iterator<T>::deref_lhs {
    const my_ostream_iterator<T>& it;
public:
    deref_lhs(const my_ostream_iterator<T>& it_)
        : it(it_) {}
    template<typename T1>
    deref_lhs& operator=(T1&& rhs) {
        it.os << std::forward<T1&&>(rhs) << it.sep;
        return *this;
    }
};

int main() {
    const int data[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    std::copy(std::begin(data), std::end(data),
              my_ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

