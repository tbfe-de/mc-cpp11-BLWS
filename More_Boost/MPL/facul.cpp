/*
 ====================================================
 Beispiel 1: Metaprogrammierung mit Templates
 Zur Compile-Zeit Fakultaet eines Wertes ausrechnen
 (praktischer Nutzen: ????)
 ====================================================
*/

// allgemeiner Fall (rekursiver Aufruf)
//
template <int v>
struct facul {
	static const int value = v * facul<v-1>::value;
};

// spezieller Fall (rekursionsabbruch)
//
template<>
struct facul<1> {
	static const int value = 1;
};

// nur zur Demonstration -- erzeugtes Programm ist
// aequivalent zu   std::cout << 120 << std::endl;
//
#include <iostream>
int main() {
	std::cout << facul<5>::value << std::endl;
}
