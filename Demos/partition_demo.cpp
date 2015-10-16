#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <iostream>
#include <vector>

int main() {
    std::array<int, 15> data;
    std::iota(data.begin(), data.end(), 1);
    auto partition_point = std::partition(data.begin(), data.end(),
                                          [](int e) { return (e % 2); });
    std::cout << "-> ";
    std::copy(data.begin(), partition_point, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    std::cout << "-> ";
    std::copy(partition_point, data.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}
