#include <iostream>

#include <boost/mpl/list.hpp>

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

// Einfache Ereignisse (ohne Daten)
//
struct EvDQuote : sc::event<EvDQuote> {};
struct EvSlash : sc::event<EvSlash> {};
struct EvAsterisk : sc::event<EvAsterisk> {};
struct EvEndline : sc::event<EvEndline>	{};

// Ereignis mit Daten
//
struct EvOther		: sc::event<EvOther>	{
	EvOther(char ch_) : ch(ch_) {}
	const char ch;
};

// Voraus-Deklaration der Zustände (notwendig wegen teilweise gegenseitiger Bezugnahme)
//
struct Source;
struct StrLiteral;
struct B_Comment;
struct E_Comment;
struct CStyleComment;
struct CppStyleComment;

// Eigentliche Zustandsmachine (beinhaltet Ausfuehrbarkeit, Uebergangsregeln getrennt)
//
struct RemoveComments
	: sc::state_machine< RemoveComments , Source > {
	RemoveComments(std::ostream& os_)
		: os(os_)
	{}
	void out(const char ch) {
		os << ch;
	}
private:
	std::ostream& os;
};

// Zustand 'Source': Aktionen und Uebergaenge
//
struct Source
	: sc::simple_state< Source, RemoveComments > {
	typedef mpl::list<
		sc::transition< EvSlash, B_Comment >,
		sc::custom_reaction< EvOther >,
		sc::custom_reaction< EvEndline >,
		sc::custom_reaction< EvAsterisk >,
		sc::custom_reaction< EvDQuote >
	> reactions;

	sc::result react(const EvOther& ev) {
		context< RemoveComments >().out(ev.ch);
		return transit< Source >();
	}

	sc::result react(const EvDQuote& ev) {
		context< RemoveComments >().out('"');
		return transit< StrLiteral >();
	}

	sc::result react(const EvAsterisk& ev) {
		context< RemoveComments >().out('*');
		return transit< StrLiteral >();
	}

	sc::result react(const EvEndline& ev) {
		context< RemoveComments >().out('\n');
		return transit< Source >();
	}
};

// Zustand 'StrLiteral': Aktionen und Uebergaenge
//
struct StrLiteral
	: sc::simple_state< StrLiteral, RemoveComments > {
	typedef mpl::list<
		sc::custom_reaction< EvSlash >,
		sc::custom_reaction< EvAsterisk >,
		sc::custom_reaction< EvEndline >,
		sc::custom_reaction< EvDQuote >,
		sc::custom_reaction< EvOther >
	> reactions;

	sc::result react(const EvSlash& ev) {
		context< RemoveComments >().out('/');
		return transit< StrLiteral >();
	}

	sc::result react(const EvAsterisk& ev) {
		context< RemoveComments >().out('*');
		return transit< StrLiteral >();
	}

	sc::result react(const EvDQuote& ev) {
		context< RemoveComments >().out('"');
		return transit< Source >();
	}

	sc::result react(const EvOther& ev) {
		context< RemoveComments >().out(ev.ch);
		return transit< StrLiteral >();
	}

	sc::result react(const EvEndline& ev) {
		context< RemoveComments >().out('\n');
		return transit< Source >();
	}
};

// Zustand 'B_Comment': Aktionen und Uebergaenge
//
struct B_Comment
	: sc::simple_state< B_Comment, RemoveComments > {
	typedef mpl::list<
		sc::transition< EvAsterisk, CStyleComment >,
		sc::transition< EvSlash	  , CppStyleComment >,
		sc::custom_reaction< EvOther >
	> reactions;

	sc::result react(const EvOther& ev) {
		context< RemoveComments >().out('/');
		context< RemoveComments >().out(ev.ch);
		return transit< Source >();
	}
};

// Zustand 'E_Comment': Nur Uebergaenge
//
struct E_Comment
	: sc::simple_state< E_Comment, RemoveComments > {
	typedef mpl::list<
		sc::transition< EvAsterisk, E_Comment >,
		sc::transition<	EvSlash	  , Source >
	> reactions;
};

// Zustand 'CStyleComment': Nur Uebergaenge
//
struct CStyleComment
	: sc::simple_state< CStyleComment, RemoveComments > {
	typedef mpl::list<
		sc::transition< EvAsterisk, E_Comment >,
		sc::transition< EvOther	  , CStyleComment >
	> reactions;
};

// Zustand 'CStyleComment': Aktionen und Uebergaenge
// (abschliessendes Newline wird ausgegeben)
//
struct CppStyleComment
	: sc::simple_state< CppStyleComment, RemoveComments > {
	typedef mpl::list<
		sc::custom_reaction< EvEndline >
	> reactions;

	sc::result react(const EvEndline& ev) {
		context< RemoveComments >().out('\n');
		return transit< Source >();
	}
};

// Verarbeiten der Eingabe (Uebergabe am Automaten als Ereignis)
//
void process(std::istream& is, std::ostream& os) {
	RemoveComments cr(os);
	cr.initiate();
	char ch;
	while (is.get(ch)) {
		switch (ch) {
		case '"':
			cr.process_event(EvDQuote());
			break;
		case '/':
			cr.process_event(EvSlash());
			break;
		case '*':
			cr.process_event(EvAsterisk());
			break;
		case '\n':
			cr.process_event(EvEndline());
			break;
		default:
			cr.process_event(EvOther(ch));
			break;
		}
	}
}

#if 1
int main() {
	process(std::cin, std::cout);
}
#else

#ifdef CK

#include "Util/CK/CK.h"

#include <sstream>

int main() {
	using namespace std;

/////////////////////////////////////////////////////////////////////////////////
CK_section("Empty Input .......................................................")
/////////////////////////////////////////////////////////////////////////////////
	{
		stringstream iss("");
		ostringstream oss;
		process(iss, oss);
CK_compare(	iss.eof()		, true					)
CK_compare(	oss.str()		, ""					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("No Commment .......................................................")
/////////////////////////////////////////////////////////////////////////////////
	{
		stringstream iss("no comment"	"\n"
				 "(two lines)"	"\n"
		);
		ostringstream oss;
		process(iss, oss);
CK_compare(	iss.eof()		, true					)
CK_compare(	oss.str()		, "no comment"	"\n"
					  "(two lines)"	"\n"			)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("All C-Style Comment ...............................................")
/////////////////////////////////////////////////////////////////////////////////
	{
		stringstream iss("/* here it starts ..."	"\n"
				 "... and it ends here */"	"\n"
		);
		ostringstream oss;
		process(iss, oss);
CK_compare(	iss.eof()		, true					)
CK_compare(	oss.str()		, "\n"					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("All C++-Style Comment .............................................")
/////////////////////////////////////////////////////////////////////////////////
	{
		stringstream iss("// here it starts ..."	"\n"
				 "// ... and it end here"	"\n"
		);
		ostringstream oss;
		process(iss, oss);
CK_compare(	iss.eof()		, true					)
CK_compare(	oss.str()		, "\n"
					  "\n"					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("Mixed C/C++-Style Comments ........................................")
/////////////////////////////////////////////////////////////////////////////////
	{
		stringstream iss(
			"a /*simple*/ test is this ..."		"\n"
			"a = b/2; // <-- a division !!"		"\n"
		);
		ostringstream oss;
		process(iss, oss);
CK_compare(	iss.eof()		, true					)
CK_compare(	oss.str()		, "a  test is this ..."	"\n"
					  "a = b/2; "		"\n"		)
	}
}

#endif

#ifdef CX

#include "cxtime.c"

#include <sstream>

int main() {
	using namespace std;
	string input(
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
		"a /*simple*/ test is this ..."		"\n"
		"*a = b/2; // <-- a division !!"	"\n"
	);
	string output(
		"a  test is this ..."	"\n"
		"*a = b/2; "		"\n"
	);
	CXTIME(
		"Simple test for Boost.Statechart"
	,
		istringstream iss(input);
		ostringstream oss;
	,
		process(iss, oss);
	,
	,
	);
		
}

#endif
#endif
