#include "Util/CK/CK.h"

#include <algorithm>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

class Maxer3 {
	unsigned value;
public:
	Maxer3() : value(0) {}
	void operator()(const unsigned int& v) {
		if ((v%3 == 0) && (value < v))
			value = v;
	}
	unsigned getValue() const {
		return value;
	}
};

template<typename InputIterator, typename BodyCode>
void my_for_each(InputIterator start, InputIterator end, BodyCode run) {
	typedef typename boost::unwrap_reference<BodyCode>::type WrappedClass;
	while (start != end)
		static_cast<WrappedClass&>(run)(*start++);
}

struct Maxer3Ref : boost::reference_wrapper<Maxer3> {
	Maxer3Ref(Maxer3 &m) : boost::reference_wrapper<Maxer3>(m) {}
	void operator()(const unsigned int v) {
		static_cast<Maxer3&>(*this)(v);
	}
};

const unsigned int data[] = { 2u, 7u, 19u, 23u, 27u, 28u, 6u, 31u, 7u, 0u };
const std::size_t N = sizeof data / sizeof data[0];

int main() {
		Maxer3 m3;
CK_section(	"Result for my_for_each .............."			)
		my_for_each(data, data + N, m3);
CK_compare(	m3.getValue(),				0		)
		my_for_each(data, data + N, boost::ref(m3));
CK_compare(	m3.getValue(),				27		)
		std::for_each(data, data + N, m3);
CK_section(	"Result for data std::foreach ........"			)
CK_compare(	m3.getValue(),				0		)
		std::for_each(data, data + N,
			      boost::bind<void>(boost::ref(m3), _1));
CK_compare(	m3.getValue(),				27		)
}
