#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <iostream>
#include <vector>

int main() {
    std::array<int, 15> data;
    std::iota(data.begin(), data.end(), 1);
    std::vector<int> result;
//  std::copy(data.begin(), data.end(), std::back_insert_iterator<std::vector<int>>(result));
//  std::copy(data.begin(), data.end(), std::back_inserter(result));
    std::copy_if(data.begin(), data.end(), std::back_inserter(result),
                 [](int e) { return (e % 2); });
    std::cout << "-> ";
    for (auto v : result)
        std::cout << v << ' ';
    std::cout << '\n';
}
