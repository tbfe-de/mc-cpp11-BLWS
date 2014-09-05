#include <algorithm>			 	// copy, min
#include <cstdio>			 	// EOF
#include <iosfwd>			 	// streamsize
#include <boost/iostreams/categories.hpp>	// source_tag

template<typename Container>
class container_source {
public:
	typedef typename Container::value_type char_type;
	typedef boost::iostreams::source_tag category;
	container_source(const Container& container)
		: container_(container), pos_(0)
	{}
	std::streamsize read(char_type s[], std::streamsize n) {
		using namespace std;
		streamsize amt = static_cast<streamsize>(container_.size() - pos_);
		streamsize result = (min)(n, amt);
		if (result == 0)
			return EOF;
		copy(container_.begin() + pos_,
		     container_.begin() + pos_ + result,
		     s);
		pos_ += result;
		return result;
	}
	Container& container() { return container_; }
private:
	typedef typename Container::size_type size_type;
	const Container& container_;
	size_type pos_;
};


#include <string>
#include <vector>
#include <boost/iostreams/stream.hpp>

#include "Util/CK/CK.h"

int main() {
	using namespace std;
	namespace io = boost::iostreams;

	typedef container_source<string> string_source;
	typedef vector<wchar_t> wchar_vector;
	typedef container_source<wchar_vector> wchar_vector_source;

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'container_source<string>' (empty input) ..................")
/////////////////////////////////////////////////////////////////////////////////
	{
		io::stream<string_source> in("");
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, EOF					)
CK_compare(	in.good()		, false					)
CK_compare(	in.fail()		, true					)
CK_compare(	in.eof()		, true					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'container_source<string>' (3 char input) .................")
/////////////////////////////////////////////////////////////////////////////////
	{
		const string input ("abc");
		io::stream<string_source> in(input);
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, 'a'					)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, 'b'					)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, 'c'					)
CK_compare(	in.get()		, EOF					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}

/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'container_source<string>' (multiple lines) ...............")
/////////////////////////////////////////////////////////////////////////////////
	{
		const string input(
			"Hello World!"				"\n"
			"whatever is going on ..."		"\n"
			"... please let me know"		"\n"
		);
		io::stream<string_source> in(input);
		string line;
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	&getline(in, line)	, &in					)
CK_compare(	line			, "Hello World!"			)
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
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}


/////////////////////////////////////////////////////////////////////////////////
CK_section("Example 'container_source<wchar_vector>' ..........................")
/////////////////////////////////////////////////////////////////////////////////
	typedef vector<wchar_t> wchar_vector;
	typedef container_source<wchar_vector> wchar_vector_source;
	{
		wchar_vector data;
		data.push_back(L'§');
		data.push_back(L'€');
		io::stream<wchar_vector_source> in(data);
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, L'§'					)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, L'€'					)
CK_compare(	in.good()		, true					)
CK_compare(	in.fail()		, false					)
CK_compare(	in.eof()		, false					)
CK_compare(	in.get()		, EOF					)
CK_compare(	in.good()		, false					)
CK_compare(	in.eof()		, true					)
	}

}
