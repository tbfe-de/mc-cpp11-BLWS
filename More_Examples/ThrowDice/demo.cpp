#include <random>
#include <iostream>

int throw_dice() {
    static std::random_device rd;
    static std::mt19937 gen{/*std::random_device{}()*/};
    static std::uniform_int_distribution<> dis{1, 6};
    return dis(gen);
}

int main() {
    for (int i = 0; i < 20; ++i)
        std::cout << throw_dice() << ' ';
    std::cout << std::endl;
}

