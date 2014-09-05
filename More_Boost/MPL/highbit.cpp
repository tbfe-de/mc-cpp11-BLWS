/*
 ====================================================
 Beispiel 2: Metaprogrammierung mit Templates
 Zur Compile-Zeit das höchstwertige Bit einer Zahl
 bestimmen (praktischer Nutzen: z.B. Anzahl der zur
 Abspeicherung des Werts notwendigen Bits bestimmen)
 ====================================================
*/

template <int v>
struct highbit {
	static const int value = highbit<(v >> 1)>::value + 1;
};

template<>
struct highbit<1> {
	static const int value = 0;
};

#include <iostream>
int main() {
	std::cout << highbit<60>::value << std::endl;
     // aber Compilezeitfehler bei folgendem:
     // ......... << highbit<0>::value ......
}
