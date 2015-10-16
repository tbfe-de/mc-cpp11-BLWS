#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <iostream>
#include <vector>

int main() {
//  std::array<int, 5> data;
//  std::fill(data.begin(), data.end(), 1);
#if 0
    std::vector<double> data(5);
    std::generate(data.begin(), data.end(), 
                  [count = 1.5]() mutable { auto old = count; count += 3.7; return old; } );
#else
    std::vector<int> data({1});
    assert(!data.empty());
//  std::generate_n(std::back_inserter(data), 5, [v = data.back()]() mutable { return v *= 2; });
    std::generate_n(std::back_inserter(data), 5, [&data]() { return data.back()*2; });
#endif
    std::cout << "-> ";
    for (auto v : data)
        std::cout << v << ' ';
    std::cout << '\n';
}
