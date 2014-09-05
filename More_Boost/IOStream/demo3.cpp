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
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>

#include "Util/CK/CK.h"

int main(int argc, char *argv[]) {
	using namespace std;

	namespace io = boost::iostreams;

	io::filtering_istream in;
	in.push(shell_comments_input_filter());

	ifstream fs;
	if (argc == 1)
		in.push(cin);
	else {
		fs.open(argv[1]);
		if (!fs.good()) {
			cerr << "file cannot be read: " << argv[1] << endl;
			return EXIT_FAILURE;
		}
		in.push(fs);
	}	
	string s;
	while (getline(in, s)) {
		if (!s.empty()) 
			cout << s << endl;
	}
	// fs is closed automatically when going out of scope;

}
