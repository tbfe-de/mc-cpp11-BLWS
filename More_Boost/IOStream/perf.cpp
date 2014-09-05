#include <iostream>
#include <iomanip>

void join_lines_function(std::istream& is, std::ostream& os) {
	char current;
	while (is.get(current)) {
		if (current != '\\') {
			os.put(current);
			continue;
		}
		if (!is.get(current)) {
			return;
		}
		if (current == '\n') {
			continue;
		}
		os.put('\\');
		os.put(current);
	}
}

void remove_shell_comments_function(std::istream& is, std::ostream& os) {
	bool skip = false;
	char current;
	while (is.get(current)) {
		if (skip && current != '\n') {
			continue;
		}
		if ((skip = (current == '#'))) {
			continue;
		}
		os.put(current);
	}
}

void remove_shell_comments_join_lines_function(std::istream& is, std::ostream& os) {
	bool skip = false;
	char current;
	while (is.get(current)) {
		if (skip && current != '\n') {
			continue;
		}
		if ((skip = (current == '#'))) {
			continue;
		}
		if (current != '\\') {
			if (current == '\n')
				skip = false;
			if (!skip)
				os.put(current);
			continue;
		}
		if (!is.get(current)) {
			if (!skip)
				os.put('\\');
			return;
		}
		if (current == '\n') {
			if (skip) {
				skip = false;
				os.put('\n');
			}
			continue;
		}
		os.put('\\');
		os.put(current);
	}
}

void join_lines_remove_shell_comments_function(std::istream& is, std::ostream& os) {
	bool skip = false;
	char current;
	while (is.get(current)) {
		if (skip) {
			if (current != '\n' && current != '\\')
				continue;
		}
		else if ((skip = (current == '#'))) {
			continue;
		}
		if (current != '\\') {
			if (current == '\n')
				skip = false;
			if (!skip)
				os.put(current);
			continue;
		}
		if (!is.get(current)) {
			if (!skip)
				os.put('\\');
			return;
		}
		if (skip || current == '\n')
			continue;
		os.put('\\');
		os.put(current);
	}
}

#include <boost/iostreams/char_traits.hpp> // EOF, WOULD_BLOCK
#include <boost/iostreams/concepts.hpp>    // input_filter
#include <boost/iostreams/operations.hpp>  // get

namespace io = boost::iostreams;

class join_lines_filter
	: public boost::iostreams::input_filter {
public:
	join_lines_filter()
		: saved(EOF)
	{}

	template<typename Source>
	int get(Source& src) {
		if (saved != EOF) {
			const int result(saved);
			saved = EOF;
			return result;
		}
		for (;;) {
			const int current(boost::iostreams::get(src));
			if (current != '\\'
			 || (saved = boost::iostreams::get(src)) != '\n')
				return current;
			saved = EOF;
		}
	}

	template<typename Source>
	void close(Source&) {
		saved = EOF;
	}
private:
	int saved;
};

class remove_shell_comments_filter
	: public boost::iostreams::input_filter {
public:
	remove_shell_comments_filter()
		: skip(false)
	{}

	template<typename Source>
	int get(Source& src) {
		for (;;) {
			const int current(boost::iostreams::get(src));
			if (current == EOF
			 || current == boost::iostreams::WOULD_BLOCK)
				return current;
			if (skip) {
				if (current != '\n')
					continue;
				skip = false;
			}
			else if (current == '#') {
				skip = true;
				continue;
			}
			return current;
		}
	}

	template<typename Source>
	void close(Source&) {
		skip = false;
	}
private:
	bool skip;
};

#include <cassert>
#include <sstream>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>

#include "Util/CxTime/CXTIME.h"

void copy_helper(io::filtering_istream& input, std::ostream& output) {
	char c;
	while (input.get(c) && c)
		output.put(c);
}

#define X10(t)\
	t t t t t t t t t t
//	1-2-3-4-5-6-7-8-9-10

#define X(t) X10(X10(t))

const char test_input[] = {X(
		"#!special-processing"				"\n"
		"This is the first line"			"\n"
		"and a second one ... \\"			"\n"
		"continuing here. # YEP!"			"\n"
		"This \\one\\ is critical #<----\\"		"\n"
		"?comment?"					"\n"
		"#WORK-COMPLETED#"				"\n"
)};
const char linejoined_output[] = {X(
		"#!special-processing"				"\n"
		"This is the first line"			"\n"
		"and a second one ... continuing here. # YEP!"	"\n"
		"This \\one\\ is critical #<----?comment?"	"\n"
		"#WORK-COMPLETED#"				"\n"
)};
const char uncommented_output[] = {X(
		""						"\n"
		"This is the first line"			"\n"
		"and a second one ... \\"			"\n"
		"continuing here. "				"\n"
		"This \\one\\ is critical "			"\n"
		"?comment?"					"\n"
		""						"\n"
)};
const char uncommented_linejoined_output[] = {X(
		""						"\n"
		"This is the first line"			"\n"
		"and a second one ... continuing here. "	"\n"
		"This \\one\\ is critical "			"\n"
		"?comment?"					"\n"
		""						"\n"
)};
const char linejoined_uncommented_output[] = {X(
		""						"\n"
		"This is the first line"			"\n"
		"and a second one ... continuing here. "	"\n"
		"This \\one\\ is critical "			"\n"
		""						"\n"
)};
int main() {

	using namespace std;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Joining lines (specialized function)"
	,
		istringstream is(test_input);
		ostringstream os;
	,
		join_lines_function(is, os);
	,
		assert(os.str() == linejoined_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Joining lines (Boost.Iostream filter)"
	,
		io::filtering_istream in;
		in.push(join_lines_filter());
		in.push(boost::make_iterator_range(test_input));
		ostringstream os;
	,
		copy_helper(in, os);
	,	
		assert(os.str() == linejoined_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Uncommenting lines (specialized function)"
	,
		istringstream is(test_input);
		ostringstream os;
	,
		remove_shell_comments_function(is, os);
	,
		assert(os.str() == uncommented_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Uncommenting lines (Boost.Iostream filter)"
	,
		io::filtering_istream in;
		in.push(remove_shell_comments_filter());
		in.push(boost::make_iterator_range(test_input));
		ostringstream os;
	,
		copy_helper(in, os);
	,	
		assert(os.str() == uncommented_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Uncommenting and joining lines (specialized function)"
	,
		istringstream is(test_input);
		ostringstream os;
	,
		remove_shell_comments_join_lines_function(is, os);
	,
		assert(os.str() == uncommented_linejoined_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Uncommenting and joining lines (Boost.Iostream filter)"
	,
		io::filtering_istream in;
		in.push(join_lines_filter());
		in.push(remove_shell_comments_filter());
		in.push(boost::make_iterator_range(test_input));
		ostringstream os;
	,
		copy_helper(in, os);
	,	
		assert(os.str() == uncommented_linejoined_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Joining and uncommenting lines (specialized function)"
	,
		istringstream is(test_input);
		ostringstream os;
	,
		join_lines_remove_shell_comments_function(is, os);
	,
		assert(os.str() == linejoined_uncommented_output);
	,
	);
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	CXTIME( "Joining and uncommenting lines (Boost.Iostream filter)"
	,
		io::filtering_istream in;
		in.push(remove_shell_comments_filter());
		in.push(join_lines_filter());
		in.push(boost::make_iterator_range(test_input));
		ostringstream os;
	,
		copy_helper(in, os);
	,	
		assert(os.str() == linejoined_uncommented_output);
	,
	);
}
