#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
//  std::array<int, 5> data;
//  std::fill(data.begin(), data.end(), 1);
    std::vector<double> data(5);
    double z = 0.7;
    std::cout << ++z << std::endl;
    std::iota(data.begin(), data.end(), 1.5);
    std::cout << "-> ";
    for (auto v : data)
        std::cout << v << ' ';
    std::cout << '\n';
}
