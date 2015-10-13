/*
 * Ermittlung von Ziffernwiederholung und aufsteigenden
 * Ziffernfolgen in Zufallszahlen 1000..9999
 * (siehe aufgabe.txt Abschnitt 3d)
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

const long long ROLLS = 100000;

int main() {
	using namespace std;

	cout << "... from " << ROLLS
	     << " randoms generated in range 1000..9999:" << endl;
	RandFromRange r1(1, 9);
	RandFromRange r2(0, 9);
	int gte2seq = 0;
	int riseseq = 0;
	for (decltype(ROLLS+0) i = 0; i < ROLLS; ++i) {
		bool rising = true;
		for (int same, last = -1, i = 0; i < 4;) {
			const auto rnd = ((i == 0) ? r1 : r2)();
			if (rnd <= last)
				rising = false;
			if (rnd != last) {
				same = 1;
				last = rnd;
			}
			else {
				if (++same == 2)
					++gte2seq;
			}
			++i;
		}
		if (rising)
			++riseseq;
	}
	cout.precision(2);
        cout << "--- " << gte2seq
	     << " (= " << (100.0*gte2seq) / ROLLS << "%)"
		" have >= 2 adjacent same digits" << endl;
        cout << "--- " << riseseq
	     << " (= " << (100.0*riseseq) / ROLLS << "%)"
		" have (strictly) rising digits" << endl;
}
