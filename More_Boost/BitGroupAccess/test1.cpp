#include "named_bits.h"

// -------------------------------------------------------------
// SPECIFIC CODE HERE (adapts generic code to specific needs)
//
//       Bit: 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
enum FBB { //--------------------|-----|  |  |  |-----|--------
	FOO= BOOST_BINARY( 0  0  0  0  0  0  0  0  0  1  0  0 ),
	BAR= BOOST_BINARY( 0  0  0  0  1  1  1  1  0  0  0  0 ),
	BAZ= BOOST_BINARY( 0  0  1  0  0  0  0  0  0  0  0  0 ),
}; //                    BAZ-bit-^     |BAR-bits|     ^-FOO-bit

// -------------------------------------------------------------
// TYPICAL CLIENT SIDE CODE (making use of adapted generic code)
//
void xxx() {
	extern unsigned short ov;
	named_bits<FBB>::uval<BAR>(&ov, 3u);
}
int yyy() {
	extern unsigned short ov;
	return named_bits<FBB>::uval<BAR, unsigned short>(&ov);
}

