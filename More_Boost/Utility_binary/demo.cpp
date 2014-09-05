/* Exercise: Utility_Binary/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for BOOST_BINARY from 'Boost.Utility'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2012): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
 * The use of BOOST_BINARY in this example is rather minor because the bulk of
 * code has quite a different objective: is implementing a (template) class to
 * allow easy access to single bits or groups of bits in larger storage unit
 * (like a byte, a word, ...).
 * To achieve this in a performant way a fair amount of 'Metaprogramming with
 * Templates' is necessary because certain properties from bit-patterns (which
 * are the constants defined with BOOST_BINARY) needs to be calculated at
 * compile-time.
 *
 * Note that the section "GENERIC CODE" below is only contained for easier
 * reference and would typically be placed into a header file of its own!
 *
 * See also directory 'NamedBits' for a more realistic layout of this example
 * (wrt. to distribution among header files, unit tests, performance evaluation
 * and comparison to classical 'C bitfields') and directory 'CPP11' for how to
 * replace compile-time calculations with 'constexpr' functions.
*/

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                            GENERIC CODE BEGIN

template<typename P, P v, int d= 1>
struct enum_rightshift {
	static const unsigned long ulong_value=
		static_cast<unsigned long>(v) >> d;
	static const P enum_value=
		static_cast<P>(ulong_value);
	static const bool lost_bits=
		(static_cast<unsigned long>(v) & 0x1) == 0x1;
};

template<typename P, P sel, bool= false>
struct bm_shift {
	typedef enum_rightshift<P, sel> shifted;
	static const int value=
		1 + bm_shift<P, shifted::enum_value, shifted::lost_bits>::value;
};

template<typename P, P sel>
struct bm_shift<P, sel, true> {
	static const int value= -1;
};

template<typename P, P sel>
struct bm_mask {
	typedef enum_rightshift<P, sel, bm_shift<P, sel>::value> t;
	static const unsigned long value= t::ulong_value;
};

template<typename P, typename S= unsigned long>
class W {
private:
	S store;
public:
	W() : store(0) {}
	template<P sel>
	S peek() const {
		return (store >> bm_shift<P, sel>::value) & bm_mask<P, sel>::value;
	}
	template<P sel, typename R>
	void poke(R w) {
		store&= ~(bm_mask<P, sel>::value << bm_shift<P, sel>::value);
		store|= (w & bm_mask<P, sel>::value) << bm_shift<P, sel>::value;
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
