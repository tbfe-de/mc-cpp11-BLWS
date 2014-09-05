#include <boost/iostreams/char_traits.hpp> // EOF, WOULD_BLOCK
#include <boost/iostreams/concepts.hpp>    // input_filter
#include <boost/iostreams/operations.hpp>  // get

class shell_comments_input_filter : public boost::iostreams::input_filter {
public:
	explicit
	shell_comments_input_filter(char comment_char = '#')
		: comment_char_(comment_char)
		, skip_(false)
	{}

	template<typename Source>
	int get(Source& src)
	{
		int c;
		for (;;) {
			c = boost::iostreams::get(src);
			if (c == EOF || c == boost::iostreams::WOULD_BLOCK)
				break;
			if (c == comment_char_)
				skip_ = true;
			else if (c == '\n')
				skip_ = false;
			if (!skip_)
				break;
		}
		return c;
	}

	template<typename Source>
	void close(Source&) { skip_ = false; }
private:
	const char comment_char_;
	bool skip_;
};

#include <string>
#include <vector>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>

#include "Util/CK/CK.h"

int main() {
	using namespace std;
	namespace io = boost::iostreams;

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'shell comment filter' (empty input) ......................")
/////////////////////////////////////////////////////////////////////////////////
	{
		io::filtering_istream in;
		in.push(shell_comments_input_filter());
		in.push(boost::make_iterator_range(string()));
		string line;
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'shell comment filter' (one line -- no comment) ...........")
/////////////////////////////////////////////////////////////////////////////////
	{
		string input("Hi ...!\n");
		io::filtering_istream in;
		in.push(shell_comments_input_filter());
		in.push(boost::make_iterator_range(input));
		string line;
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, "Hi ...!"				)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'shell comment filter' (one line -- only comments) ........")
/////////////////////////////////////////////////////////////////////////////////
	{
		string input("# no-no\n");
		io::filtering_istream in;
		in.push(shell_comments_input_filter());
		in.push(boost::make_iterator_range(input));
		string line;
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, ""					)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'shell comment filter' (one line -- text + comment) .......")
/////////////////////////////////////////////////////////////////////////////////
	{
		string input("yep #!!\n");
		io::filtering_istream in;
		in.push(shell_comments_input_filter());
		in.push(boost::make_iterator_range(input));
		string line;
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, "yep "				)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}
/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'shell comment filter' (mixed input) ......................")
/////////////////////////////////////////////////////////////////////////////////
	{
		const string input(
			"Hello World!      # <-- start line"	"\n"
			"whatever is going on ..."		"\n"
			"... please let me know"		"\n"
			"#EOF#"					"\n"
		);
		io::filtering_istream in;
		in.push(shell_comments_input_filter());
		in.push(boost::make_iterator_range(input));
		string line;
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, "Hello World!      "			)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, "whatever is going on ..."		)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, "... please let me know"		)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, ""					)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}

}
