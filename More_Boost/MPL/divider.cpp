/*
 ====================================================
 Beispiel 3: Metaprogrammierung mit Templates
 Zur Compile-Zeit eine Division der Art
	variable / konstante
 optimieren (unter der Annahme, das so etwas wie das
 folgende der Compiler nicht von sich aus macht und
 eine Shift-Operation tatsaechlich schneller als eine
 Divisions-Operazion ist).

 Dieses Beispiel nutzt in boost::mpl definierte
 Hilfsklassen wie etwa "if_", um eine aehnliche
 Syntax zu erzielen wie man sie aus ueblichen
 Programmiersprachen kennt. Bei der Kompilierung muss
 daher der Pfad zu den Header-Files der Boost-Library
 angegeben werden.
 ====================================================
*/

#include <boost/mpl/eval_if.hpp>
#include <iostream>

// Bestimmung des hoechsten gesetzten Bits in einer Konstanten
//
template <int v>
struct highbit {
	static const int value = highbit<(v >> 1)>::value + 1;
};
template<>
struct highbit<1> {
	static const int value = 0;
};

// Bestimmung ob eine Zahl 2er-Potenz (groesser 0) ist
//
template<int v>
struct pwrof2 {
	static const bool value = ((v & 1u) == 0) && pwrof2<(v >> 1)>::value;
};
template<>
struct pwrof2<2> {
	static const bool value = true;
};
template<>
struct pwrof2<1> {
	static const bool value = false;
};
template<>
struct pwrof2<0> {
	static const bool value = false;
};

// drei Versionen der Division:
//	- allgemeiner Fall
//	- wenn im Nenner eine 2er-Potenz steht
//	- wenn im Nenner eine 1 steht
template<int n>
struct generic {
	static int divide(int v) {
		std::cout << "(... using divide ...) ";
		return v / n;
	}
};
template<int n>
struct fast {
	static int divide(int v) {
		std::cout << "(... using shift ...) ";
		return v >> highbit<n>::value;
	}
};
struct nothing {
	static int divide(int v) {
		std::cout << "(... nothing ...) ";
		return v;
	}
};

// Auswahl der "optimalen" Version der Division
//
template<int n>
struct best : boost::mpl::if_<
	pwrof2<n>,
	fast<n>,
	typename boost::mpl::if_<
		boost::mpl::bool_<n != 1>,
		generic<n>,
		nothing
	>::type
> {};

// Demo-Programm:
//
#define DIVISOR 5
#ifndef DIVISOR
#error please compile with ... -Ipath_to_boost -DDIVISOR=number ...
#endif
int main() {
	int dividend;
	std::cout << "(compiled for DIVISOR=" << DIVISOR << ")" << std::endl;
	while (std::cin >> dividend)
		std::cout << best<DIVISOR>::type::divide(dividend) << std::endl;
}
