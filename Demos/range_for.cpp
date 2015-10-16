#include <iostream>
#include <vector>
#include <initializer_list>

//int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
std::vector<int> primes({ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 });
//std::vector<int> primes({2});
//auto primes = { 2.2, 3, 5.1, 7, 11, 13, 17, 19, 23, 29 };


int main() {
#if  1
    for (const int &prm : primes) {
        std::cout << prm << '\n';
    }
#else
    {
        auto &container = primes;
        auto current = std::begin(container);
        auto end = std::end(container);
        for (; current != end; ++current) {
            const int &prm = *current;
            std::cout << prm << '\n';
        }
    }
#endif
}


