#include <iostream>

#include <boost/ref.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

using msm::front::Row;
using msm::front::none;

// Einfache Ereignisse (ohne Daten)
//
struct EvSlash {};
struct EvAsterisk {};
struct EvDQuote {};
struct EvEndline {};

// Ereigniss mit Daten
//
struct EvOther {
	EvOther(char ch_) : ch(ch_) {}
	const char ch;
};

struct RemoveComments : public msm::front::state_machine_def<RemoveComments> {

        struct Source_tag {};
        typedef msm::front::euml::func_state<Source_tag> Source; 

        struct B_Comment_tag {};
        typedef msm::front::euml::func_state<B_Comment_tag> B_Comment; 

        struct E_Comment_tag {};
        typedef msm::front::euml::func_state<E_Comment_tag> E_Comment; 

        struct CStyleComment_tag {};
        typedef msm::front::euml::func_state<CStyleComment_tag> CStyleComment; 

        struct CppStyleComment_tag {};
        typedef msm::front::euml::func_state<CppStyleComment_tag> CppStyleComment; 

        struct StrLiteral_tag {};
        typedef msm::front::euml::func_state<StrLiteral_tag> StrLiteral; 

        typedef Source initial_state;

	RemoveComments(std::ostream& os_)
		: os(os_)
	{}

        struct outAsterisk {
            template <class EVT,class FSM, class SourceState,class TargetState>
            void operator()(EVT const&, FSM& fsm, SourceState&, TargetState&) {
                fsm.out('*');
            }
        };

        struct outEndline {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const&, FSM& fsm, SourceState&, TargetState&) {
                fsm.out('\n');
            }
        };

        struct outDQuote {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const&, FSM& fsm, SourceState&, TargetState&) {
                fsm.out('"');
            }
        };

        struct outSlash {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const&, FSM& fsm, SourceState&, TargetState&) {
                fsm.out('/');
            }
        };

        struct outOther {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ev, FSM& fsm, SourceState&, TargetState&) {
                fsm.out(ev.ch);
            }
        };

        struct outSlashOther {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ev, FSM& fsm, SourceState&, TargetState&) {
                fsm.out('/');
		fsm.out(ev.ch);
            }
        };

	struct transition_table : mpl::vector<
	//  	Start  		, Event  	  Next  	          Action  	  Guard  	
	// 	+---------------+---------------+-----------------------+---------------+-------+
	Row < 	Source		, EvSlash	, B_Comment		, none		, none 	>,
	Row < 	Source		, EvAsterisk	, Source		, outAsterisk	, none 	>,
	Row < 	Source		, EvEndline	, Source		, outEndline	, none 	>,
	Row < 	Source		, EvDQuote      , StrLiteral		, outDQuote	, none 	>,
	Row < 	Source		, EvOther	, Source		, outOther	, none 	>,
	// 	+---------------+---------------+-----------------------+---------------+-------+
	Row < 	B_Comment	, EvAsterisk	, CStyleComment		, none		, none 	>,
	Row < 	B_Comment	, EvSlash	, CppStyleComment	, none		, none 	>,
	Row < 	B_Comment	, EvOther	, Source		, outSlashOther	, none 	>,
	// 	+---------------+---------------+-----------------------+---------------+-------+
	Row < 	CStyleComment	, EvAsterisk	, E_Comment		, none		, none 	>,
	// 	+---------------+---------------+-----------------------+---------------+-------+
	Row < 	E_Comment	, EvSlash	, Source		, none		, none 	>,
	Row < 	E_Comment	, EvAsterisk	, E_Comment		, none		, none 	>,
	Row < 	E_Comment	, EvOther	, CStyleComment		, none		, none 	>,
	// 	+---------------+---------------+-----------------------+---------------+-------+
	Row < 	CppStyleComment	, EvEndline	, Source		, outEndline	, none 	>,
	// 	+---------------+---------------+-----------------------+---------------+-------+
	Row < 	StrLiteral	, EvSlash	, StrLiteral		, outSlash	, none 	>,
	Row < 	StrLiteral	, EvAsterisk	, StrLiteral		, outAsterisk	, none 	>,
	Row < 	StrLiteral	, EvEndline	, Source		, outEndline	, none 	>,
	Row < 	StrLiteral	, EvDQuote      , Source		, outDQuote	, none 	>,
	Row < 	StrLiteral	, EvOther	, StrLiteral		, outOther	, none 	>
	// 	+---------------+---------------+-----------------------+---------------+-------+
	> {};

        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& e, FSM&,int state)
        {
        }

private:
	std::ostream& os;
	void out(const char ch) {
		os << ch;
	}

};

void process(std::istream& is, std::ostream& os) {
	msm::back::state_machine<RemoveComments> cr(boost::ref(os));
	cr.start();
	char ch;
	while (is.get(ch)) {
		switch (ch) {
		case '/':
			cr.process_event(EvSlash());
			break;
		case '*':
			cr.process_event(EvAsterisk());
			break;
		case '\n':
			cr.process_event(EvEndline());
			break;
		case '"':
			cr.process_event(EvDQuote());
			break;
		default:
			cr.process_event(EvOther(ch));
			break;
		}
	}
}

int main() {
	process(std::cin, std::cout);
}

#if 0

#if 0

#include "Util/CK/CK.h"

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

#else

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
		"*a = b/2; // <-- a division !!"		"\n"
	);
	string output(
		"a  test is this ..."	"\n"
		"*a = b/2; "		"\n"
	);
	CXTIME(
		"Simple test for Boost.Msm"
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
