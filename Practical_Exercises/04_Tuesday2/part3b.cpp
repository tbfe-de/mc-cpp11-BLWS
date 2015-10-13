/*
 * Erzeugung von Zufallszahlen 0..9999 auf zwei Arten
 * (siehe aufgabe.txt Abschnitt 3b)
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

class RandFromRange {
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dis;
public:
	RandFromRange(int lo, int hi)
		: rd(), gen(rd()), dis(lo, hi)
	{}
	int operator()() {
		return dis(gen);
	}
};

const long long ROLLS = 100;

int main() {
	using namespace std;

	// generate numbers between 0 and 9999
	RandFromRange r1(0, 9999);
	vector<int> v1;
	cout << "1st set of " << ROLLS << " randoms in range 0..9999 ..." << flush;
	for (decltype(ROLLS+0) i = 0; i < ROLLS; ++i)
		v1.push_back(r1());
	cout << " sum-up to avg: "
	     << accumulate(v1.begin(), v1.end(), 0uLL) / ROLLS << endl;
		
	// again generate numbers between 0 and 9999
	RandFromRange r2(0, 9);
	vector<int> v2;
	cout << "2nd set of " << ROLLS << " randoms in range 0..9999 ..." << flush;
	for (decltype(ROLLS+0) i = 0; i < ROLLS; ++i)
		v2.push_back(r2() + 10*r2() + 100*r2() + 1000*r2());
	cout << " sum-up to avg: "
	     << accumulate(v2.begin(), v2.end(), 0uLL) / ROLLS << endl;
}
