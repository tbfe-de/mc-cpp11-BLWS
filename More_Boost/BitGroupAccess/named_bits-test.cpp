#include "named_bits.h"

#include "boost/utility/binary.hpp"
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
#include "Util/CK/CK.h"

void test_Internal_Helpers_static() {
CK_section(	"Internal helpers: static offset and mask ...."	)
		typedef unsigned int uint; uint offset, mask;

		offset= bitgroup_offset<FBB, FOO, uint>::value;
		mask= bitgroup_mask<FBB, FOO, uint>::value;
CK_compare(	offset					, 2	)
CK_compare(	mask					, 0x1	)

		offset= bitgroup_offset<FBB, BAR, uint>::value;
		mask= bitgroup_mask<FBB, BAR, uint>::value;
CK_compare(	offset					, 4	)
CK_compare(	mask					, 0xF	)

		offset= bitgroup_offset<FBB, BAZ, uint>::value;
		mask= bitgroup_mask<FBB, BAZ, uint>::value;
CK_compare(	offset					, 9	)
CK_compare(	mask					, 0x1	)

}

void test_Internal_Helpers_dynamic() {
CK_section(	"Internal helpers: dynamic offset and mask ..."	)

CK_compare(	bitgroup_offset_value<uint>(FOO)	, 2	)
CK_compare(	bitgroup_mask_value<uint>(FOO)		, 0x1	)

CK_compare(	bitgroup_offset_value<uint>(BAR)	, 4	)
CK_compare(	bitgroup_mask_value<uint>(BAR)		, 0xF	)

CK_compare(	bitgroup_offset_value<uint>(BAZ)	, 9	)
CK_compare(	bitgroup_mask_value<uint>(BAZ)		, 0x1	)

}

void test_Object_raw_bits() {
		named_bits<FBB>::var<unsigned short> bv;
CK_section(	"Accessing raw bits in object ................"	)
		bv.rawbits(0xACE);
CK_compare(	bv.rawbits()				, 0xACE	)
		bv.rawbits(0xBED);
CK_compare(	bv.rawbits()				, 0xBED	)
		bv.rawbits(0xDEADBEEF);
CK_compare(	bv.rawbits()				, 0xBEEF)
	
}

void test_Overlay_peek() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Peek bit(s) using overlay ..................."	)
CK_compare(	t::peek<FOO>(&ov)			, 0	)
CK_compare(	t::peek<BAR>(&ov)			, 0	)
CK_compare(	t::peek<BAZ>(&ov)			, 0	)
		ov= 0xDEADBEEF;
CK_compare(	t::peek<FOO>(&ov)			, 0x004	)
CK_compare(	t::peek<BAR>(&ov)			, 0x0E0	)
CK_compare(	t::peek<BAZ>(&ov)			, 0x200	)
}

void test_Overlay_peek_dynamic() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Dynamic peek bit(s) using overlay ..........."	)
CK_compare(	t::peek(FOO, &ov)			, 0	)
CK_compare(	t::peek(BAR, &ov)			, 0	)
CK_compare(	t::peek(BAZ, &ov)			, 0	)
		ov= 0xDEADBEEF;
CK_compare(	t::peek(FOO, &ov)			, 0x004	)
CK_compare(	t::peek(BAR, &ov)			, 0x0E0	)
CK_compare(	t::peek(BAZ, &ov)			, 0x200	)
}

void test_Object_peek() {
		named_bits<FBB>::var<> bv(0u);
CK_section(	"Peek bit(s) using object ...................."	)
CK_compare(	bv.peek<FOO>()				, 0	)
CK_compare(	bv.peek<BAR>()				, 0	)
CK_compare(	bv.peek<BAZ>()				, 0	)
		bv.rawbits(0xDEADBEEF);
CK_compare(	bv.peek<FOO>()				, 0x004	)
CK_compare(	bv.peek<BAR>()				, 0x0E0	)
CK_compare(	bv.peek<BAZ>()				, 0x200	)
}

void test_Object_peek_dynamic() {
		named_bits<FBB>::var<> bv(0u);
CK_section(	"Dynamic peek bit(s) using object ............"	)
CK_compare(	bv.peek(FOO)				, 0	)
CK_compare(	bv.peek(BAR)				, 0	)
CK_compare(	bv.peek(BAZ)				, 0	)
		bv.rawbits(0xDEADBEEF);
CK_compare(	bv.peek(FOO)				, 0x004	)
CK_compare(	bv.peek(BAR)				, 0x0E0	)
CK_compare(	bv.peek(BAZ)				, 0x200	)
}

void test_Overlay__poke() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Poke bit(s) using overlay ..................."	)
		t::_poke<FOO>(&ov, 0x004);
CK_compare(	ov					, 0x004	)
		t::_poke<BAR>(&ov, 0x030);
CK_compare(	ov 					, 0x034	)
		t::_poke<BAR>(&ov, 0x0D0);
CK_compare(	ov 					, 0x0D4	)
		t::_poke<BAZ>(&ov, 0x200);
CK_compare(	ov 					, 0x2D4	)
		t::_poke<FOO>(&ov, 0x000);
CK_compare(	ov 					, 0x2D0	)
		t::_poke<BAR>(&ov, 0x000);
CK_compare(	ov 					, 0x200	)
		t::_poke<BAZ>(&ov, 0x000);
CK_compare(	ov 					, 0x000	)
}

void test_Overlay__poke_dynamic() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Dynamic poke bit(s) using overlay ..........."	)
		t::_poke(FOO, &ov, 0x004);
CK_compare(	ov					, 0x004	)
		t::_poke(BAR, &ov, 0x030);
CK_compare(	ov 					, 0x034	)
		t::_poke(BAR, &ov, 0x0D0);
CK_compare(	ov 					, 0x0D4	)
		t::_poke(BAZ, &ov, 0x200);
CK_compare(	ov 					, 0x2D4	)
		t::_poke(FOO, &ov, 0x000);
CK_compare(	ov 					, 0x2D0	)
		t::_poke(BAR, &ov, 0x000);
CK_compare(	ov 					, 0x200	)
		t::_poke(BAZ, &ov, 0x000);
CK_compare(	ov 					, 0x000	)
}

void test_Object__poke() {
		named_bits<FBB>::var<> bv(0u);
CK_section(	"Poke bit(s) using object ...................."	)
		bv._poke<FOO>(0x004);
CK_compare(	bv.rawbits()				, 0x004	)
		bv._poke<BAR>(0x030);
CK_compare(	bv.rawbits()				, 0x034	)
		bv._poke<BAR>(0x0D0);
CK_compare(	bv.rawbits()				, 0x0D4	)
		bv._poke<BAZ>(0x200);
CK_compare(	bv.rawbits()				, 0x2D4	)
		bv._poke<FOO>(0x000);
CK_compare(	bv.rawbits()				, 0x2D0	)
		bv._poke<BAR>(0x000);
CK_compare(	bv.rawbits()				, 0x200	)
		bv._poke<BAZ>(0x000);
CK_compare(	bv.rawbits()				, 0x000	)
}

void test_Overlay_poke() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Secure poke bit(s) using overlay ............"	)
		t::poke<FOO>(&ov, 0x004);
CK_compare(	ov					, 0x004	)
		t::poke<BAR>(&ov, 0x030);
CK_compare(	ov 					, 0x034	)
		t::poke<BAR>(&ov, 0x0D0);
CK_compare(	ov 					, 0x0D4	)
		t::poke<BAR>(&ov, 0x2D0);
CK_compare(	ov 					, 0x0D4	)
		t::poke<BAZ>(&ov, 0x200);
CK_compare(	ov 					, 0x2D4	)
		t::poke<FOO>(&ov, 0x000);
CK_compare(	ov 					, 0x2D0	)
		t::poke<BAR>(&ov, 0x000);
CK_compare(	ov 					, 0x200	)
		t::poke<BAZ>(&ov, 0x000);
CK_compare(	ov 					, 0x000	)
}

void test_Overlay_poke_dynamic() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Secure poke bit(s) using overlay ............"	)
		t::poke(FOO, &ov, 0x004);
CK_compare(	ov					, 0x004	)
		t::poke(BAR, &ov, 0x030);
CK_compare(	ov 					, 0x034	)
		t::poke(BAR, &ov, 0x0D0);
CK_compare(	ov 					, 0x0D4	)
		t::poke(BAR, &ov, 0x2D0);
CK_compare(	ov 					, 0x0D4	)
		t::poke(BAZ, &ov, 0x200);
CK_compare(	ov 					, 0x2D4	)
		t::poke(FOO, &ov, 0x000);
CK_compare(	ov 					, 0x2D0	)
		t::poke(BAR, &ov, 0x000);
CK_compare(	ov 					, 0x200	)
		t::poke(BAZ, &ov, 0x000);
CK_compare(	ov 					, 0x000	)
}

void test_Object_poke() {
		named_bits<FBB>::var<> bv(0u);
CK_section(	"Secure poke bit(s) using object ............."	)
		bv.poke<FOO>(0x004);
CK_compare(	bv.rawbits()				, 0x004	)
		bv.poke<BAR>(0x030);
CK_compare(	bv.rawbits()				, 0x034	)
		bv.poke<BAR>(0x0D0);
CK_compare(	bv.rawbits()				, 0x0D4	)
		bv.poke<BAR>(0x2D0);
CK_compare(	bv.rawbits()				, 0x0D4	)
		bv.poke<BAZ>(0x200);
CK_compare(	bv.rawbits()				, 0x2D4	)
		bv.poke<FOO>(0x000);
CK_compare(	bv.rawbits()				, 0x2D0	)
		bv.poke<BAR>(0x000);
CK_compare(	bv.rawbits()				, 0x200	)
		bv.poke<BAZ>(0x000);
CK_compare(	bv.rawbits()				, 0x000	)
}

void test_Overlay__rpoke() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Returning poke bit(s) using overlay ........."	)
CK_compare(	t::_rpoke<FOO>(&ov, 0x004)		, 0x000 )
CK_compare(	t::_rpoke<BAR>(&ov, 0x030)		, 0x000 )
CK_compare(	t::_rpoke<BAR>(&ov, 0x0D0)		, 0x030 )
CK_compare(	t::_rpoke<BAZ>(&ov, 0x200)		, 0x000	)
CK_compare(	t::_rpoke<FOO>(&ov, 0x000)		, 0x004	)
CK_compare(	t::_rpoke<BAR>(&ov, 0x000)		, 0x0D0	)
CK_compare(	t::_rpoke<BAZ>(&ov, 0x000)		, 0x200	)
}

void test_Object__rpoke() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Returning poke bit(s) using object .........."	)
CK_compare(	bv._rpoke<FOO>(0x004)			, 0x000 )
CK_compare(	bv._rpoke<BAR>(0x030)			, 0x000 )
CK_compare(	bv._rpoke<BAR>(0x0D0)			, 0x030 )
CK_compare(	bv._rpoke<BAZ>(0x200)			, 0x000	)
CK_compare(	bv._rpoke<FOO>(0x000)			, 0x004	)
CK_compare(	bv._rpoke<BAR>(0x000)			, 0x0D0	)
CK_compare(	bv._rpoke<BAZ>(0x000)			, 0x200	)
}

void test_Overlay_rpoke() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Returning secure poke bit(s) using overlay .."	)
CK_compare(	t::rpoke<FOO>(&ov, 0x004)		, 0x000 )
CK_compare(	t::rpoke<BAR>(&ov, 0x030)		, 0x000 )
CK_compare(	t::rpoke<BAR>(&ov, 0x0D0)		, 0x030 )
CK_compare(	t::rpoke<BAR>(&ov, 0x2D0)		, 0x0D0	)
CK_compare(	t::rpoke<BAZ>(&ov, 0x200)		, 0x000	)
CK_compare(	t::rpoke<FOO>(&ov, 0x000)		, 0x004	)
CK_compare(	t::rpoke<BAR>(&ov, 0x000)		, 0x0D0	)
CK_compare(	t::rpoke<BAZ>(&ov, 0x000)		, 0x200	)
}

void test_Object_rpoke() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Returning secure poke bit(s) using object ..."	)
CK_compare(	bv.rpoke<FOO>(0x004)			, 0x000 )
CK_compare(	bv.rpoke<BAR>(0x030)			, 0x000 )
CK_compare(	bv.rpoke<BAR>(0x0D0)			, 0x030 )
CK_compare(	bv.rpoke<BAR>(0x2D0)			, 0x0D0	)
CK_compare(	bv.rpoke<BAZ>(0x200)			, 0x000	)
CK_compare(	bv.rpoke<FOO>(0x000)			, 0x004	)
CK_compare(	bv.rpoke<BAR>(0x000)			, 0x0D0	)
CK_compare(	bv.rpoke<BAZ>(0x000)			, 0x200	)
}

void test_Overlay_uval() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Unsigned value access using overlay ........."	)
CK_compare(	t::uval<FOO>(&ov)			, 0	)
CK_compare(	t::uval<BAR>(&ov)			, 0	)
CK_compare(	t::uval<BAZ>(&ov)			, 0	)
		t::uval<FOO>(&ov, 1);
CK_compare(	t::uval<FOO>(&ov)			, 1	)
CK_compare(	t::uval<BAR>(&ov)			, 0	)
CK_compare(	t::uval<BAZ>(&ov)			, 0	)
		t::uval<BAR>(&ov, 6);
CK_compare(	t::uval<FOO>(&ov)			, 1	)
CK_compare(	t::uval<BAR>(&ov)			, 6	)
CK_compare(	t::uval<BAZ>(&ov)			, 0	)
		t::uval<BAR>(&ov, 9);
CK_compare(	t::uval<FOO>(&ov)			, 1	)
CK_compare(	t::uval<BAR>(&ov)			, 9	)
CK_compare(	t::uval<BAZ>(&ov)			, 0	)
		t::uval<BAR>(&ov, 19);
CK_compare(	t::uval<FOO>(&ov)			, 1	)
CK_compare(	t::uval<BAR>(&ov)			, 3	)
CK_compare(	t::uval<BAZ>(&ov)			, 0	)
		t::uval<BAZ>(&ov, 1);
CK_compare(	t::uval<FOO>(&ov)			, 1	)
CK_compare(	t::uval<BAR>(&ov)			, 3	)
CK_compare(	t::uval<BAZ>(&ov)			, 1	)
		t::uval<FOO>(&ov, 0);
CK_compare(	t::uval<FOO>(&ov)			, 0	)
CK_compare(	t::uval<BAR>(&ov)			, 3	)
CK_compare(	t::uval<BAZ>(&ov)			, 1	)
}

void test_Object_uval() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Unsigned value access using object .........."	)
CK_compare(	bv.uval<FOO>()				, 0	)
CK_compare(	bv.uval<BAR>()				, 0	)
CK_compare(	bv.uval<BAZ>()				, 0	)
		bv.uval<FOO>(1);
CK_compare(	bv.uval<FOO>()				, 1	)
CK_compare(	bv.uval<BAR>()				, 0	)
CK_compare(	bv.uval<BAZ>()				, 0	)
		bv.uval<BAR>(6);
CK_compare(	bv.uval<FOO>()				, 1	)
CK_compare(	bv.uval<BAR>()				, 6	)
CK_compare(	bv.uval<BAZ>()				, 0	)
		bv.uval<BAR>(9);
CK_compare(	bv.uval<FOO>()				, 1	)
CK_compare(	bv.uval<BAR>()				, 9	)
CK_compare(	bv.uval<BAZ>()				, 0	)
		bv.uval<BAR>(19);
CK_compare(	bv.uval<FOO>()				, 1	)
CK_compare(	bv.uval<BAR>()				, 3	)
CK_compare(	bv.uval<BAZ>()				, 0	)
		bv.uval<BAZ>(1);
CK_compare(	bv.uval<FOO>()				, 1	)
CK_compare(	bv.uval<BAR>()				, 3	)
CK_compare(	bv.uval<BAZ>()				, 1	)
		bv.uval<FOO>(0);
CK_compare(	bv.uval<FOO>()				, 0	)
CK_compare(	bv.uval<BAR>()				, 3	)
CK_compare(	bv.uval<BAZ>()				, 1	)
}

void test_Overlay_sval() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Signed value access using overlay ..........."	)
CK_compare(	(t::sval<BAR, int>(&ov))		, 0	)
CK_compare(	ov					, 0x00	)
		t::sval<BAR>(&ov, 1);
CK_compare(	(t::sval<BAR, int>(&ov))		, 1	)
CK_compare(	ov					, 0x10	)
		t::sval<BAR>(&ov, 6);
CK_compare(	(t::sval<BAR, int>(&ov))		, 6	)
CK_compare(	ov					, 0x60	)
		t::sval<BAR>(&ov, 7);
CK_compare(	(t::sval<BAR, int>(&ov))		, 7	)
CK_compare(	ov					, 0x70	)
		t::sval<BAR>(&ov, 0);
CK_compare(	(t::sval<BAR, int>(&ov))		, 0	)
CK_compare(	ov					, 0x00	)
		t::sval<BAR>(&ov, -1);
CK_compare(	(t::sval<BAR, int>(&ov))		, -1	)
CK_compare(	ov					, 0xF0	)
		t::sval<BAR>(&ov, -6);
CK_compare(	(t::sval<BAR, int>(&ov))		, -6	)
CK_compare(	ov					, 0xA0	)
		t::sval<BAR>(&ov, -7);
CK_compare(	(t::sval<BAR, int>(&ov))		, -7	)
CK_compare(	ov					, 0x90	)
		t::sval<BAR>(&ov, -8);
CK_compare(	(t::sval<BAR, int>(&ov))		, -8	)
CK_compare(	ov					, 0x80	)
		t::sval<BAR>(&ov, 8);
CK_compare(	(t::sval<BAR, int>(&ov))		, -8	)
CK_compare(	ov					, 0x80	)
		t::sval<BAR>(&ov, -9);
CK_compare(	(t::sval<BAR, int>(&ov))		, 7	)
CK_compare(	ov					, 0x70	)
}

void test_Object_sval() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Signed value access using object ............"	)
CK_compare(	(bv.sval<BAR, int>())			, 0	)
CK_compare(	bv.rawbits()				, 0x00	)
		bv.sval<BAR>(1);
CK_compare(	(bv.sval<BAR, int>())			, 1	)
CK_compare(	bv.rawbits()				, 0x10	)
		bv.sval<BAR>(6);
CK_compare(	(bv.sval<BAR, int>())			, 6	)
CK_compare(	bv.rawbits()				, 0x60	)
		bv.sval<BAR>(7);
CK_compare(	(bv.sval<BAR, int>())			, 7	)
CK_compare(	bv.rawbits()				, 0x70	)
		bv.sval<BAR>(0);
CK_compare(	(bv.sval<BAR, int>())			, 0	)
CK_compare(	bv.rawbits()				, 0x00	)
		bv.sval<BAR>(-1);
CK_compare(	(bv.sval<BAR, int>())			, -1	)
CK_compare(	bv.rawbits()				, 0xF0	)
		bv.sval<BAR>(-6);
CK_compare(	(bv.sval<BAR, int>())			, -6	)
CK_compare(	bv.rawbits()				, 0xA0	)
		bv.sval<BAR>(-7);
CK_compare(	(bv.sval<BAR, int>())			, -7	)
CK_compare(	bv.rawbits()				, 0x90	)
		bv.sval<BAR>(-8);
CK_compare(	(bv.sval<BAR, int>())			, -8	)
CK_compare(	bv.rawbits()				, 0x80	)
		bv.sval<BAR>(8);
CK_compare(	(bv.sval<BAR, int>())			, -8	)
CK_compare(	bv.rawbits()				, 0x80	)
		bv.sval<BAR>(-9);
CK_compare(	(bv.sval<BAR, int>())			, 7	)
CK_compare(	bv.rawbits()				, 0x70	)
}

void test_Overlay_ruval() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Returning unsigned value access using overlay"	)
CK_compare(	t::ruval<FOO>(&ov, 1)			, 0	)
CK_compare(	t::ruval<BAR>(&ov, 3)			, 0	)
CK_compare(	t::ruval<BAR>(&ov, 9)			, 3	)
CK_compare(	t::ruval<BAR>(&ov, 19)			, 9	)
CK_compare(	t::ruval<BAZ>(&ov, 1)			, 0	)
CK_compare(	t::ruval<BAZ>(&ov, 0)			, 1	)
CK_compare(	t::ruval<BAR>(&ov, 0)			, 3	)
CK_compare(	t::ruval<FOO>(&ov, 0)			, 1	)
}

void test_Object_ruval() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Returning unsigned value access using object "	)
CK_compare(	bv.ruval<FOO>(1)			, 0	)
CK_compare(	bv.ruval<BAR>(3)			, 0	)
CK_compare(	bv.ruval<BAR>(9)			, 3	)
CK_compare(	bv.ruval<BAR>(19)			, 9	)
CK_compare(	bv.ruval<BAZ>(1)			, 0	)
CK_compare(	bv.ruval<BAZ>(0)			, 1	)
CK_compare(	bv.ruval<BAR>(0)			, 3	)
CK_compare(	bv.ruval<FOO>(0)			, 1	)
}

void test_Overlay_incr() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Increment/decrement using overlay ..........."	)
		t::val_incr<BAR>(&ov, 1);
CK_compare(	ov					, 0x10	)
		t::val_incr<BAR>(&ov, 2);
CK_compare(	ov					, 0x30	)
		t::val_incr<BAR>(&ov, 3);
CK_compare(	ov					, 0x60	)
		t::val_incr<BAR>(&ov, -1);
CK_compare(	ov					, 0x50	)
		t::val_incr<BAR>(&ov, 2);
CK_compare(	ov					, 0x70	)
		t::val_incr<BAR>(&ov, 1);
CK_compare(	ov					, 0x80	)
		t::val_incr<BAR>(&ov, 1);
CK_compare(	ov					, 0x90	)
		t::val_incr<BAR>(&ov, 2);
CK_compare(	ov					, 0xB0	)
		t::val_incr<BAR>(&ov, 17);
CK_compare(	ov					, 0xC0	)
		t::val_incr<BAR>(&ov, 15);
CK_compare(	ov					, 0xB0	)
		t::val_incr<BAR>(&ov, -7);
CK_compare(	ov					, 0x40	)
}

void test_Object_incr() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Increment/decrement using object ............"	)
		bv.val_incr<BAR>(1);
CK_compare(	bv.rawbits()				, 0x10	)
		bv.val_incr<BAR>(2);
CK_compare(	bv.rawbits()				, 0x30	)
		bv.val_incr<BAR>(3);
CK_compare(	bv.rawbits()				, 0x60	)
		bv.val_incr<BAR>(-1);
CK_compare(	bv.rawbits()				, 0x50	)
		bv.val_incr<BAR>(2);
CK_compare(	bv.rawbits()				, 0x70	)
		bv.val_incr<BAR>(1);
CK_compare(	bv.rawbits()				, 0x80	)
		bv.val_incr<BAR>(1);
CK_compare(	bv.rawbits()				, 0x90	)
		bv.val_incr<BAR>(2);
CK_compare(	bv.rawbits()				, 0xB0	)
		bv.val_incr<BAR>(17);
CK_compare(	bv.rawbits()				, 0xC0	)
		bv.val_incr<BAR>(15);
CK_compare(	bv.rawbits()				, 0xB0	)
		bv.val_incr<BAR>(-7);
CK_compare(	bv.rawbits()				, 0x40	)
}

void test_Overlay_bitops() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Bit operations using overlay ................"	)
CK_compare(	t::bit<FOO>(&ov)			, false	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
		t::bit_set<FOO>(&ov);
CK_compare(	t::bit<FOO>(&ov)			, true	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
		t::bit_clear<FOO>(&ov);
CK_compare(	t::bit<FOO>(&ov)			, false	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
		t::bit<FOO>(&ov, true);
CK_compare(	t::bit<FOO>(&ov)			, true	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
		t::bit<FOO>(&ov, false);
CK_compare(	t::bit<FOO>(&ov)			, false	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
		t::bit_flip<FOO>(&ov);
CK_compare(	t::bit<FOO>(&ov)			, true	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
		t::bit_flip<FOO>(&ov);
CK_compare(	t::bit<FOO>(&ov)			, false	)
CK_compare(	t::bit<BAZ>(&ov)			, false	)
}

void test_Overlay_bitops_dynamic() {
		typedef named_bits<FBB> t;
		unsigned long ov(0uL);
CK_section(	"Dynamic bit operations using overlay ........"	)
CK_compare(	t::bit(FOO, &ov)			, false	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
		t::bit_set(FOO, &ov);
CK_compare(	t::bit(FOO, &ov)			, true	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
		t::bit_clear(FOO, &ov);
CK_compare(	t::bit(FOO, &ov)			, false	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
		t::bit(FOO, &ov, true);
CK_compare(	t::bit(FOO, &ov)			, true	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
		t::bit(FOO, &ov, false);
CK_compare(	t::bit(FOO, &ov)			, false	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
		t::bit_flip(FOO, &ov);
CK_compare(	t::bit(FOO, &ov)			, true	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
		t::bit_flip(FOO, &ov);
CK_compare(	t::bit(FOO, &ov)			, false	)
CK_compare(	t::bit(BAZ, &ov)			, false	)
}

void test_Object_bitops() {
		named_bits<FBB>::var<> bv(0uL);
CK_section(	"Bit operations using object ................."	)
CK_compare(	bv.bit<FOO>()				, false	)
CK_compare(	bv.bit<BAZ>()				, false	)
		bv.bit_set<FOO>();
CK_compare(	bv.bit<FOO>()				, true	)
CK_compare(	bv.bit<BAZ>()				, false	)
		bv.bit_clear<FOO>();
CK_compare(	bv.bit<FOO>()				, false	)
CK_compare(	bv.bit<BAZ>()				, false	)
		bv.bit<FOO>(true);
CK_compare(	bv.bit<FOO>()				, true	)
CK_compare(	bv.bit<BAZ>()				, false	)
		bv.bit<FOO>(false);
CK_compare(	bv.bit<FOO>()				, false	)
CK_compare(	bv.bit<BAZ>()				, false	)
		bv.bit_flip<FOO>();
CK_compare(	bv.bit<FOO>()				, true	)
CK_compare(	bv.bit<BAZ>()				, false	)
		bv.bit_flip<FOO>();
CK_compare(	bv.bit<FOO>()				, false	)
CK_compare(	bv.bit<BAZ>()				, false	)
}

int main() {
	test_Internal_Helpers_static();
	test_Internal_Helpers_dynamic();
	test_Object_raw_bits();
	test_Overlay_peek();
	test_Overlay_peek_dynamic();
	test_Object_peek();
	test_Object_peek_dynamic();
	test_Overlay__poke();
	test_Overlay__poke_dynamic();
	test_Object__poke();
	test_Overlay_poke();
	test_Object_poke();
	test_Overlay__rpoke();
	test_Object__rpoke();
	test_Overlay_rpoke();
	test_Object_rpoke();
	test_Overlay_uval();
	test_Object_uval();
	test_Overlay_sval();
	test_Object_sval();
	test_Overlay_ruval();
	test_Object_ruval();
	test_Overlay_incr();
	test_Object_incr();
	test_Overlay_bitops();
	test_Overlay_bitops_dynamic();
	test_Object_bitops();
}

