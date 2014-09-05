#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

#include <boost/range.hpp>
#include <boost/range/algorithm/for_each.hpp>

class Person {
	const char* name;
public:
	Person(const char*n) : name(n) {
		cout << "Person " << name << " erzeugt\n";
	}
	~Person() {
		cout << "Person " << name << " geloescht\n";
	}
};

template<typename T>
void genericDelete(T) {
}

int main() {
	map<const int, Person*> data;
	data.insert(make_pair(1, new Person("Hans")));
	data.insert(make_pair(2, new Person("Claudia")));
	data.insert(make_pair(12, new Person("Karlheinz")));

	// was immer ...

	boost::range::for_each(data,
		[] (pair<const int, Person*> &d) {
			delete d.second;
			d.second = 0;
		}
	);
#endif

}
