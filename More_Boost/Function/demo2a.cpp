#include <boost/format.hpp>
	using boost::format;
	using boost::io::group;
#include <boost/function.hpp>

#include <iostream>
	using namespace std;

const bool all[]= { false, true };
const bool *const all_begin= &all[0];
const bool *const all_end= &all[2];

struct Operation1 {
	virtual const char* name() const =0;
	virtual bool operator()(bool) const =0;
};

struct Operation2 {
	virtual const char* name() const =0;
	virtual bool operator()(bool, bool) const =0;
};

inline
void show_op1(const Operation1& op, ostream &os) {
	for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
		os << format("%s %|-5| => %||\n")
			% op.name()
			% group(boolalpha, *rhs)
			% group(boolalpha, op(*rhs));
	}
}

inline
void show_op2(const Operation2& op, ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| %s %|-5| => %||\n")
				% group(boolalpha, *lhs)
				% op.name()
				% group(boolalpha, *rhs)
				% group(boolalpha, op(*lhs, *rhs));
		}
	}
}

struct bool_NOT : Operation1 {
	bool operator()(bool rhs) const {
		return !rhs;
	}
	const char* name() const { return "!"; }
};

struct bool_AND : Operation2 {
	bool operator()(bool lhs, bool rhs) const {
		return lhs && rhs;
	}
	const char* name() const { return "&&"; }
};

struct bool_OR : Operation2 {
	bool operator()(bool lhs, bool rhs) const {
		return lhs || rhs;
	}
	const char* name() const { return "||"; }
};

struct bool_EQ : Operation2 {
	bool operator()(bool lhs, bool rhs) const {
		return lhs == rhs;
	}
	const char* name() const { return "=="; }
};

struct bool_NE : Operation2 {
	bool operator()(bool lhs, bool rhs) const {
		return lhs != rhs;
	}
	const char* name() const { return "!="; }
};

#include <sstream>

#include "Util/CK/CK.h"

int main() {

	{
CK_section("Negation ..........................."		)
		ostringstream os;
		show_op1(bool_NOT(), os);
CK_compare(	os.str(),
		"! false => true"			"\n"
		"! true  => false"			"\n"	)
	}

	{
CK_section("Logical AND ........................"		)
		ostringstream os;
		show_op2(bool_AND(), os);
CK_compare(	os.str(),
		"false && false => false"		"\n"
		"false && true  => false"		"\n"
		"true  && false => false"		"\n"
		"true  && true  => true"		"\n"	)
	}

	{
CK_section("Logical OR ........................."		)
		ostringstream os;
		show_op2(bool_OR(), os);
CK_compare(	os.str(),
		"false || false => false"		"\n"
		"false || true  => true"		"\n"
		"true  || false => true"		"\n"
		"true  || true  => true"		"\n"	)
	}

	{
CK_section("Equality ..........................."		)
		ostringstream os;
		show_op2(bool_EQ(), os);
CK_compare(	os.str(),
		"false == false => true"		"\n"
		"false == true  => false"		"\n"
		"true  == false => false"		"\n"
		"true  == true  => true"		"\n"	)
	}

	{
CK_section("Unequality ........................."		)
		ostringstream os;
		show_op2(bool_NE(), os);
CK_compare(	os.str(),
		"false != false => false"		"\n"
		"false != true  => true"		"\n"
		"true  != false => true"		"\n"
		"true  != true  => false"		"\n"	)
	}

}

