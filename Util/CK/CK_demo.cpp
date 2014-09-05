#include <iostream>
#include <string>

class Greeter {
	std::string message;
public:
	Greeter(const std::string &m)
		: message(m)
	{}
	void sayHello(std::ostream &os, int repeat= 1) {
		do
			os << message << '\n';
		while (--repeat > 0);
	}
};

#define CK_SEPARATE_COMPILATION
#include "CK.h"

#include <sstream>

int main() {
		std::ostringstream out;
		Greeter en("hello, world");
		Greeter de("Guten Morgen");

CK_section(	"Basic Tests ..........."				)
		out.str("");
		en.sayHello(out);
CK_compare(	out.str()		, std::string("hello, world\n")	)
		out.str("");
		de.sayHello(out);
CK_compare(	out.str()		, std::string("Guten Morgen\n")	)

CK_section(	"Advanced Tests ........"				)
		out.str("");
		en.sayHello(out, 3);
CK_compare(	out.str()		, std::string("hello, world\n"
						      "hello, world\n"
						      "hello, world\n")	)
		out.str("");
		en.sayHello(out, 0);
CK_compare(	out.str()		, std::string("hello, world\n")	)
}
