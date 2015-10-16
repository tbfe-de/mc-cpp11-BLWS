#include <array>
#include <iostream>

int main() {
    std::array<int, 5> data = { 1, 2, 3, 4, 5 };
//  int data[] = { 1, 2, 3, 4, 5 };
    std::cout << "-> ";
    for (auto v : data)
        std::cout << v << ' ';
    std::cout << '\n';
}
