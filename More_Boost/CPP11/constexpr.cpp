/* Exercise: Utility_Binary/demo.cpp
 ==============================================================================
 Demonstrate new C++-11 "Functions Evaluated at Compile-Time"
 ==============================================================================
*/

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                            GENERIC CODE BEGIN

template<typename P, typename S= unsigned long>
class W {
private:
	S store;
	static inline constexpr
	int maskShift(unsigned long sel) {
		return (sel & 0x1) ? 0 : 1 + maskShift(sel >> 1);
	}
	static inline constexpr
	unsigned long maskPattern(P sel) {
		return sel >> maskShift(sel);
	}

public:
	W() : store(0) {}
	template<P sel>
	S peek() const {
		constexpr auto shift = maskShift(sel);
		constexpr auto pattern = maskPattern(sel);
		return (store >> shift) & pattern;
	}
	template<P sel, typename R>
	void poke(R w) {
		constexpr auto shift = maskShift(sel);
		constexpr auto pattern = maskPattern(sel);
		store&= ~(pattern << shift);
		store|= (w & pattern) << shift;
	}
	S rawbits() const {
		return store;
	}
	void rawbits(S w) {
		store= w;
	}
};
//	                                                       GENERIC CODE END
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                    SPECIFIC CODE STARTS HERE
#include "boost/utility/binary.hpp"

// --------------------------------------- adapt generic code to specific needs
//
// Bit: 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
enum FBB { //--------------|-----|  |  |  |-----|--------
	FOO= BOOST_BINARY( 0  0  0  0  0  0  0  1  0  0 ),
	BAR= BOOST_BINARY( 0  0  1  1  1  1  0  0  0  0 ),
	BAZ= BOOST_BINARY( 1  0  0  0  0  0  0  0  0  0 ),
}; //             BAZ bit--+    |BAR  group|    +--FOO-bit

// ------------------------------------------- make use of adapted generic code
//
#include "Util/CK/CK.h"

int main() {
		W<FBB> v;
CK_section(	"Poke bit(s) ..........................."	)
		v.poke<FOO>(1)	;
CK_compare(	v.rawbits()				, 0x004	)
		v.poke<BAR>(3)	;
CK_compare(	v.rawbits()				, 0x034	)
		v.poke<BAR>(6)	;
CK_compare(	v.rawbits()				, 0x064	)
		v.poke<BAR>(9)	;
CK_compare(	v.rawbits()				, 0x094	)
		v.poke<BAZ>(1)	;
CK_compare(	v.rawbits()				, 0x294	)
		v.poke<FOO>(false)	;
CK_compare(	v.rawbits()				, 0x290	)

CK_section(	"Peek bit(s) ..........................."	)
CK_compare(	v.peek<FOO>()				, 0	)
CK_compare(	v.peek<FOO>()				, false	)
CK_compare(	v.peek<BAR>()				, 9	)
CK_compare(	v.peek<BAZ>()				, true	)
		v.rawbits(0xDEADBEEF);
CK_compare(	v.peek<FOO>()				, 0x1	)
CK_compare(	v.peek<BAR>()				, 0xE	)
CK_compare(	v.peek<BAZ>()				, 0x1	)
}
