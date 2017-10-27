#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#if 1
#include <regex>

class regex_separator {
	std::regex rx;
public:
	regex_separator(const std::regex& rx_) : rx(rx_) {
	}
	bool operator()(std::string::const_iterator& next,
		        std::string::const_iterator end,
		        std::string& result) const {
		if (next == end) return false;
		std::smatch m;
		if (std::regex_search(next, end, m, rx)) {
			result = std::string(next, next + m.position());
			next += m.position() + m.length();
		}
		else {
			result = std::string(next, end);
			next = end;
		}
		return true;
	}
	void reset() {}
};

#include <boost/tokenizer.hpp>

int main() {
	regex_separator tokenizer_func(std::regex("--*"));
	const std::string test_input("hello-----world--now");
	boost::tokenizer<regex_separator> tok(test_input.begin(), test_input.end(), tokenizer_func);
	for (auto it = tok.begin(); it != tok.end(); ++it) {
		std::string s = *it;
		std::cout << s << std::endl;
	}
}

#else

class str_separator {
	const std::string sep;
public:
	str_separator(const std::string& sep_) : sep(sep_) {
		assert(sep.size() > 0);
	}
	bool operator()(std::string::const_iterator& next,
		        std::string::const_iterator end,
		        std::string& result) const {
		if (next == end) return false;
		auto found = std::search(next, end, sep.begin(), sep.end());
		result = std::string(next, found);
		next = (found == end) ? end : found + sep.size();
		return true;
	}
	void reset() {}
};

#include <boost/tokenizer.hpp>

int main() {
	str_separator tokenizer_func("-+-");
	//const std::string test_input("hello-+-world-+-now");
	//boost::tokenizer<str_separator> tok(test_input.begin(), test_input.end(), tokenizer_func);
	boost::tokenizer<str_separator> tok(std::string("aaaaaaaaaaaaaaaaahello-+-world-+-now"), tokenizer_func);
	for (auto it = tok.begin(); it != tok.end(); ++it) {
		std::string s = *it;
		std::cout << s << std::endl;
	}
}

#endif
