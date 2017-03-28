/*
 * Wiederholte Folgen der Laenge 4 in Zufallszahlen
 * (siehe aufgabe.txt Abschnitt 3a)
*/
#ifdef STDC_RAND
#include <cstdlib>

int roll_dice() {
	return 1 + rand() % 6;
}
#else
#include <random>

int roll_dice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution dis(1, 6);
    return dis(gen);
}
#endif

#include <cassert>
#include <iostream>

const long long ROLLS = 1000*1000;

int main() {
	using namespace std;

	cout << "... simulate rolling a dice " << ROLLS << " times:" << endl;
	int last = -1;
	int same;
	int gte4seq = 0;
	int six_seq = 0;
	for (decltype(ROLLS+0) i = 0; i < ROLLS; ++i) {
		const auto rolled = roll_dice();
		if (rolled != last) {
			same = 1;
			last = rolled;
		}
		else {
			if (++same == 4) {
				++gte4seq;
				if (rolled == 6)
					++six_seq;
			}
		}
	}
	cout << "--- same cast at least four times in a row: "
             << gte4seq << endl;
	cout << "--- from the above, a sequence of 6': " << six_seq
	     << " (= " << ( 100*six_seq/gte4seq) << "%)" << endl;
}
