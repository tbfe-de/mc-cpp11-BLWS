#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>

template<typename T1, typename T2>
void my_iota(T1 beg, T1 end, T2 val) {
    while (beg != end)
        *beg++ = val++;
}

template<typename T1, typename T2>
void my_generate(T1 beg, T1 end, T2 gen) {
    while (beg != end)
        *beg++ = gen();
}

template<typename T1, typename T2, typename T3>
void my_generate_n(T1 beg, T2 count, T3 gen) {
    while (count > 0) {
        *beg++ = gen();
        --count;
    }
}

template<typename T1, typename T2>
T2 my_copy(T1 beg, T1 end, T2 dest) {
    while (beg != end)
        *dest++ = *beg++;            // Postfix increment DOES matter !!!
//  { *dest = *beg; ++dest; ++beg; } // longer version, no matter whether
//  { *dest = *beg; dest++; beg++; } // prefix or postfix version
    return dest;
}

template<typename T1, typename T2, typename T3>
T2 my_copy_if(T1 beg, T1 end, T2 dest, T3 pred) {
    while (beg != end) {
        auto &current = *beg;
        if (pred(current))
            *dest++ = current;
        ++beg;
    }
    return dest;
}

int main() {
    std::array<int, 15> data;
    my_iota(data.begin(), data.end(), 1);
//  my_generate(data.begin(), data.end(),
    my_generate_n(data.begin(), data.size(),
//              [value = 1]() mutable { auto old = value; value *= 3; return old; });

    std::cout << "-> ";
    my_copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    std::cout << "-> ";
    my_copy_if(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "),
               [](int e) { return (e % 2); });
    std::cout << '\n';

    int result[100];
    assert(sizeof result / sizeof result[0] >= data.size());
    auto end_result = my_copy_if(data.begin(), data.end(), &result[0],
                                 [](int e) { return (e % 3) == 0; });

    std::cout << "-> ";
    my_copy(&result[0], end_result, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

}
