/*
 * Grafische Darstellung unterschiedlicher Verteilungen
 * von Zufallszahlen
 * (siehe aufgabe.txt Abschnitt 4)
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
    static std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}
#endif

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>

const long long ROLLS = 60*1000;
const int BARLEN = 70;

int main() {
	using namespace std;
	typedef unordered_map<int, long long> roll_count_t;
	roll_count_t roll_count;

	cout << "... simulate rolling a dice " << ROLLS << " times:" << endl;
	for (long i = 0; i < ROLLS; ++i)
		++roll_count[roll_dice()];
	assert(roll_count.size() == 6);
/*
	assert(accumulate_n(roll_count.begin(), roll_count.end(), 0,
			  [](const roll_count_t::value_type &e) {
				return e.second;
			  }));
*/
	const auto max = max_element(roll_count.begin(), roll_count.end(),
				     [](const roll_count_t::value_type &lhs,
					roll_count_t::value_type &rhs) {
						return lhs.second < rhs.second;
				     })->second;
	const auto scale = static_cast<double>(BARLEN)
		 	 / static_cast<double>(max);
	for (const auto &rc : roll_count) {
		const int stars = static_cast<int>(scale*rc.second + .5);
		cout << rc.first << ": ";
		fill_n(ostream_iterator<char>(cout), stars, '*');
		cout << setw(BARLEN - stars + 1) << ' ' << rc.second << endl;
	}
}
