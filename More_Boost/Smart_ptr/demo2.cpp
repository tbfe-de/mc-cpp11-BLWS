#include <iostream>
	using std::cout;
	using std::endl;
	using std::ostream;

#include <vector>
	using std::vector;

#include <boost/shared_ptr.hpp>
	using boost::shared_ptr;

class Person;
class Notary;

typedef shared_ptr<Person> PersonPtr;

class Person {
	const char *const name;
	PersonPtr mother;
	PersonPtr father;
	vector<PersonPtr> children;
	double wealth;
	bool alive;
	Person(const Person&);
	void operator=(const Person&);
public:
	Person(const char *const name_, PersonPtr mother_, PersonPtr father_, double wealth_ = 0.0)
		: name(name_)
		, mother(mother_)
		, father(father_)
		, children()
		, wealth(wealth_)
		, alive(true)
	{
		++count;
	}
	~Person() {
		--count;
	}
	static int count;

	friend class Notary;
	void die(const Notary& notary);

	friend
	ostream& operator<<(ostream& lhs, const Person& rhs) {
		return lhs
			<< rhs.name << " [" << (rhs.mother ? rhs.mother->name : "?")
					    << ";"
					    << (rhs.father ? rhs.father->name : "?")
				    << "] " << rhs.wealth;
	}
};

ostream& operator<<(ostream& lhs, const PersonPtr& rhs) {
	return lhs << *rhs;
}

int Person::count = 0;

class Notary {
	ostream& os;
public:
	Notary(ostream& os_)
		: os(os_)
	{}
	void bequest(Person& bequeathor) const {
		if (bequeathor.children.size() != 0) {
			const double amount(
				bequeathor.wealth/bequeathor.children.size()
			);
			for (vector<PersonPtr>::iterator it = bequeathor.children.begin();
							 it != bequeathor.children.end();
						       ++it) {
				os << "transfering " << amount
				   << " from " << bequeathor.name
				   << " to " << (*it)->name << endl;
				(*it)->wealth += amount;
			}
			bequeathor.wealth = 0.0;
		}
	}
};

void Person::die(const Notary& notary) {
	alive = false;
	notary.bequest(*this);
}

class Population
	:private vector<PersonPtr> {
	typedef  vector<PersonPtr> Storage;
public:
	using Storage::at;
	void addPerson(const char* const name, double wealth) {
		Storage::push_back(PersonPtr(new Person(name, PersonPtr(), PersonPtr(), wealth)));
	}
	void addProgeny(const char* const name, PersonPtr mother, PersonPtr father) {
		Storage::push_back(PersonPtr(new Person(name, mother, father)));
	}
	void print(ostream& os) {
		for (Storage::const_iterator it = Storage::begin(); it != Storage::end(); ++it) {
			os << *it << endl;
		}
	}
};

int main() {
	Population p;
	cout << "number of persons at start: " << Person::count  << endl;

	p.addPerson("karl", 50000.00);
	p.addPerson("claudia", 85000.00);
	p.addProgeny("tim", p.at(1), p.at(0));
	p.addProgeny("mona", p.at(1), p.at(0));

	p.print(cout);
	p.at(0)->die(Notary(cout));
	p.print(cout);

	cout << "number of persons at end  : " << Person::count << endl;
}
