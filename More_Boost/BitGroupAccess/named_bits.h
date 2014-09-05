#ifndef NAMED_BITS_h
#define NAMED_BITS_h

#include <cassert>

#include "boost/utility/binary.hpp"
#include "boost/static_assert.hpp"

template<typename P, P sel, typename S, int d= 1>
struct enum_rightshift {
	static const S bits_value=
		static_cast<S>(sel) >> d;
	static const P enum_value=
		static_cast<P>(bits_value);
	static const bool lost_bits=
		(static_cast<S>(sel) & 0x1) == 0x1;
};

template<typename P, P sel, typename S, bool= false>
class bitgroup_offset {
	typedef enum_rightshift<P, sel, S> rs;
public:
	static const int value=
		1 + bitgroup_offset<P, rs::enum_value, S, rs::lost_bits>::value;
};

template<typename P, P sel, typename S>
class bitgroup_offset<P, sel, S, true> {
public:
	static const int value= -1;
};

template<typename P, P sel, typename S>
class bitgroup_mask {
	typedef enum_rightshift<P, sel, S, bitgroup_offset<P, sel, S>::value> rs;
public:
	static const S value= rs::bits_value;
};

template<typename S, typename P>
int bitgroup_offset_value(P sel) {
	int result= 0;
	while (!(static_cast<S>(sel) & (1<<result)))
		++result;
	return result;
}

template<typename S, typename P>
S bitgroup_mask_value(P sel) {
	return sel >> bitgroup_offset_value<S>(sel);
}

template<typename P, P sel, typename S>
class bitgroup_convert {
	static const S hbit_mask= bitgroup_mask<P, sel, S>::value
			    & ~(bitgroup_mask<P, sel, S>::value >> 1);
public:
	template<typename R>
	static
	inline
	R bits_to_sval(S bits) {
		return static_cast<R>(bits ^ hbit_mask)
		     - static_cast<R>(hbit_mask);
	}
	template<typename R>
	static
	inline
	S sval_to_bits(R sval) {
		return (sval + static_cast<R>(hbit_mask))
		      ^ hbit_mask;
	}
};

template<typename P>
class named_bits {
public:
	// ---------------------------------------------------------------------------------
	//
	template<P sel, typename S>
	static
	inline
	S peek(const S *pbits) {
		return (*pbits & static_cast<S>(sel));
	}

	template<typename S>
	static
	inline
	S peek(P sel, const S *pbits) {
		return (*pbits & static_cast<S>(sel));
	}

	template<P sel, typename R, typename S>
	static
	inline
	void _poke(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		*pbits= (*pbits & ~static_cast<S>(sel)) | w;
	}

	template<typename R, typename S>
	static
	inline
	void _poke(P sel, S *pbits, R w) {
		*pbits= (*pbits & ~static_cast<S>(sel)) | w;
	}

	template<P sel, typename R, typename S>
	static
	inline
	void poke(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		_poke<sel, R, S>(pbits, w & static_cast<S>(sel));
	}

	template<typename R, typename S>
	static
	inline
	void poke(P sel, S *pbits, R w) {
		_poke<R, S>(sel, pbits, w & static_cast<S>(sel));
	}

	template<P sel, typename R, typename S>
	static
	inline
	S _rpoke(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		const S old(*pbits);
		*pbits= (old & ~static_cast<S>(sel)) | w;
		return old & static_cast<S>(sel);
	}

	template<P sel, typename R, typename S>
	static
	inline
	S rpoke(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		return _rpoke<sel, R, S>(pbits, w & static_cast<S>(sel));
	}

	template<P sel, typename R, typename S>
	static
	inline
	R uval(const S *pbits) {
		return (static_cast<R>(*pbits >> bitgroup_offset<P, sel, S>::value)
		       ) & bitgroup_mask<P, sel, R>::value;
	}

	template<P sel, typename S>
	static
	inline
	S uval(const S *pbits) {
		return uval<sel, S, S>(pbits);
	}

	template<P sel, typename R, typename S>
	static
	inline
	void uval(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		*pbits= *pbits & ~static_cast<S>(sel)
		     | (w << bitgroup_offset<P, sel, S>::value) & static_cast<S>(sel);
	}

	template<P sel, typename R, typename S>
	static
	inline
	S ruval(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		const S old(*pbits);
		*pbits= old & ~static_cast<S>(sel)
		     | (w << bitgroup_offset<P, sel, S>::value) & static_cast<S>(sel);
		return (old >> bitgroup_offset<P, sel, S>::value)
		     & bitgroup_mask<P, sel, S>::value;
	}

	template<P sel, typename R, typename S>
	static
	inline
	R sval(const S *pbits) {
		BOOST_STATIC_ASSERT(static_cast<R>(-1) < 0);
		return bitgroup_convert<P, sel, S>::template bits_to_sval<R>(
			(*pbits >> bitgroup_offset<P, sel, S>::value)
		      & bitgroup_mask<P, sel, S>::value
		);
	}

	template<P sel, typename R, typename S>
	static
	inline
	void sval(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		BOOST_STATIC_ASSERT(static_cast<R>(-1) < 0);
		*pbits= *pbits & ~static_cast<S>(sel)
		     | ((bitgroup_convert<P, sel, S>::template sval_to_bits<R>(w)
			 << bitgroup_offset<P, sel, S>::value) & static_cast<S>(sel));
	}

	template<P sel, typename R, typename S>
	static
	inline
	R rsval(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		BOOST_STATIC_ASSERT(static_cast<R>(-1) < 0);
		const S old(*pbits);
		*pbits= old & ~static_cast<S>(sel)
		     | ((bitgroup_convert<P, sel, S>::template sval_to_bits<R>(w)
			 << bitgroup_offset<P, sel, S>::value) & static_cast<S>(sel));
		return bitgroup_convert<P, sel, S>::template bits_to_sval<R>(
			(old >> bitgroup_offset<P, sel, S>::value) & bitgroup_mask<P, sel, S>::value

		);
	}

	template<P sel, typename R, typename S>
	static
	inline
	void val_incr(S *pbits, R w) {
		BOOST_STATIC_ASSERT(static_cast<P>(static_cast<S>(sel)) == sel);
		const S old(*pbits);
		*pbits= old & ~static_cast<S>(sel)
		     | (old + (w << bitgroup_offset<P, sel, S>::value)) & static_cast<S>(sel);
	}

	template<P sel, typename S>
	static
	inline
	bool bit(const S *pbits) {
		BOOST_STATIC_ASSERT((static_cast<S>(sel) >> bitgroup_offset<P, sel, S>::value) == 0x1);
		return *pbits & static_cast<S>(sel);
	}
	template<typename S>
	static
	inline
	bool bit(P sel, const S *pbits) {
		assert((static_cast<S>(sel) >> bitgroup_offset_value<S, P>(sel)) == 0x1);
		return *pbits & static_cast<S>(sel);
	}


	template<P sel, typename S>
	static
	inline
	void bit(S *pbits, bool w) {
		BOOST_STATIC_ASSERT((static_cast<S>(sel) >> bitgroup_offset<P, sel, S>::value) == 0x1);
		if (w)
			bit_set<sel, S>(pbits);
		else
			bit_clear<sel, S>(pbits);
	}
	template<typename S>
	static
	inline
	void bit(P sel, S *pbits, bool w) {
		assert((static_cast<S>(sel) >> bitgroup_offset_value<S, P>(sel)) == 0x1);
		if (w)
			bit_set<S>(sel, pbits);
		else
			bit_clear<S>(sel, pbits);
	}

	template<P sel, typename S>
	static
	inline
	void bit_clear(S *pbits) {
		BOOST_STATIC_ASSERT((static_cast<S>(sel) >> bitgroup_offset<P, sel, S>::value) == 0x1);
		*pbits= static_cast<P>(static_cast<S>(*pbits) & ~static_cast<S>(sel));
	}
	template<typename S>
	static
	inline
	void bit_clear(P sel, S *pbits) {
		assert((static_cast<S>(sel) >> bitgroup_offset_value<S, P>(sel)) == 0x1);
		*pbits= static_cast<P>(static_cast<S>(*pbits) & ~static_cast<S>(sel));
	}

	template<P sel, typename S>
	static
	inline
	void bit_set(S *pbits) {
		BOOST_STATIC_ASSERT((static_cast<S>(sel) >> bitgroup_offset<P, sel, S>::value) == 0x1);
		*pbits= static_cast<P>(static_cast<S>(*pbits) | static_cast<S>(sel));
	}
	template<typename S>
	static
	inline
	void bit_set(P sel, S *pbits) {
		assert((static_cast<S>(sel) >> bitgroup_offset_value<S, P>(sel)) == 0x1);
		*pbits= static_cast<P>(static_cast<S>(*pbits) | static_cast<S>(sel));
	}

	template<P sel, typename S>
	static
	inline
	void bit_flip(S *pbits) {
		BOOST_STATIC_ASSERT((static_cast<S>(sel) >> bitgroup_offset<P, sel, S>::value) == 0x1);
		*pbits= static_cast<P>(static_cast<S>(*pbits) ^ static_cast<S>(sel));
	}
	template<typename S>
	static
	inline
	void bit_flip(P sel, S *pbits) {
		assert((static_cast<S>(sel) >> bitgroup_offset_value<S, P>(sel)) == 0x1);
		*pbits= static_cast<P>(static_cast<S>(*pbits) ^ static_cast<S>(sel));
	}

	// ---------------------------------------------------------------------------------
	//
	template<typename S= unsigned int> class var;

};

template<typename P> template<typename S>
class named_bits<P>::var {
private:
	S bits;
public:
	S rawbits() const {
		return bits;
	}

	void rawbits(S w) {
		bits= w;
	}

	var() {}
	var(S init) : bits(init) {}

	template<P sel>
	inline
	S peek() const {
		return named_bits<P>::template peek<sel, S>(&bits); 
	}

	inline
	S peek(P sel) const {
		return named_bits<P>::template peek<S>(sel, &bits); 
	}

	template<P sel, typename R>
	inline
	void poke(R w) {
		named_bits<P>::template poke<sel, R, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	void _poke(R w) {
		named_bits<P>::template _poke<sel, R, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	S rpoke(R w) {
		return named_bits<P>::template rpoke<sel, R, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	S _rpoke(R w) {
		return named_bits<P>::template _rpoke<sel, R, S>(&bits, w);
	}

	template<P sel>
	inline
	S uval() const {
		named_bits<P>::template uval<sel, S, S>(&bits);
	}

	template<P sel, typename R>
	inline
	R uval() const {
		named_bits<P>::template uval<sel, R, S>(&bits);
	}

	template<P sel, typename R>
	inline
	void uval(R w) {
		named_bits<P>::template uval<sel, R, S>(&bits, w);
	}

	template<P sel>
	inline
	void uval(S w) {
		named_bits<P>::template uval<sel, S, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	S ruval(R w) {
		return named_bits<P>::template ruval<sel, R, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	void sval(R w) {
		named_bits<P>::template sval<sel, R, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	R sval() const {
		named_bits<P>::template sval<sel, R, S>(&bits);
	}

	template<P sel, typename R>
	inline
	S rsval(R w) {
		return named_bits<P>::template rsval<sel, R, S>(&bits, w);
	}

	template<P sel, typename R>
	inline
	void val_incr(R w) {
		return named_bits<P>::template val_incr<sel, R, S>(&bits, w);
	}

	template<P sel>
	inline
	bool bit() const {
		return named_bits<P>::template bit<sel>(&bits);
	}

	template<P sel>
	inline
	void bit(bool w) {
		named_bits<P>::template bit<sel>(&bits, w);
	}

	template<P sel>
	inline
	void bit_clear() {
		named_bits<P>::template bit_clear<sel>(&bits);
	}

	template<P sel>
	inline
	void bit_set() {
		named_bits<P>::template bit_set<sel>(&bits);
	}

	template<P sel>
	inline
	void bit_flip() {
		named_bits<P>::template bit_flip<sel>(&bits);
	}

};

#endif
