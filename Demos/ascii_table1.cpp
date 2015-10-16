#include <cstdio>
#include <iostream>
#include <iomanip>

int main() {
    for (int i = 32; i < 127; ++i) {
#if 1
        std::printf("'%c' - %3d - 0x%02X\n", i, i, i);
#else
        std::cout << "'" << static_cast<char>(i) << "' - "
                  << std::setw(3) << std::dec << i << " - "
                  << "0x" << std::hex << i << std::endl;
#endif
    }
}
