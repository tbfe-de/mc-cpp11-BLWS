#include <algorithm>
#include <array>
#include <iostream>

    std::array<int, 5> data;
int main() {
//  std::fill(data.begin(), data.end(), 1);
    std::fill_n(data.begin(), 3, 1);
    std::cout << "-> ";
    for (auto v : data)
        std::cout << v << ' ';
    std::cout << '\n';
}
