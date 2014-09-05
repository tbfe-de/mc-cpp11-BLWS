/*
 ==================================================================================================
 Evaluate Performance of Searching through Various Kinds of std::maps
 ==================================================================================================
 Compilation is controlled by the following macros:
   SHOW_TEST_DATA_CREATION -- print parameters forcontrolling test data creation;
   SHOW_TEST_DATA_CONTENT -- print actual content of test data;
   HAS_UNORDERED_MAP -- also add tests for unordered_map (new in C++11).
 On the command line up to four arguments can be used to set
   the size (number of elements) of the test data set;
   the length of an initial shared part of the keys [1];
   the minimum length of the keys [2];
   the maximum length of the key.
 If there are no command line arguments, cwhard-coded defaults are used (see below).

 Note 1: The reason to make this adaptable is to show the influence of key comparision.
         If there is a long shared prefix for all keys, lookup-time increases substantially
 Note 2: There is no strict guarantee that keys will be different after their shared prefix.
         Depending on the test data size there will be some - but typically very littles - overlap.
	 Furthermore for large test data sets the differing part must not be chosen sufficiently long.
         Otherwise the test simple data generating algorithm will enter an endless loop never end.
         The default of 5 chars allows for a test data of far beyond 250 million elements, shorter
	 key sizes support are: 1 char -> 50, 2 char-> 2500, 3 chars -> 100K, 4 chars -> 5M) 
*/
#ifndef SHOW_TEST_DATA_CREATION
#define SHOW_TEST_DATA_CREATION 1
#endif
#ifndef SHOW_TEST_DATA_CONTENT
#define SHOW_TEST_DATA_CONTENT 0
#endif

/**
 * Header-Files (mostly are only used to generate test-data)
*/
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#if HAS_UNORDERED_MAP
// Note: this requires C+11 (or TR1 or Boost with an additional namespace directive).
// To enable C++11 for the GNU compilers add -std=c++0x as command line option!
#include <unordered_map>
#endif
using namespace std;

/**
 * Test data types for map key and value.
*/
typedef string map_key;
struct map_value {
	const int a;
	const float b;
	const string c;
public:
	map_value(const int _a, const float _b, const string& _c)
		: a(_a), b(_b), c(_c)
	{}
};

/**
 * Variables to hold test data and to iterate over it.
 * (filled by function create_test_data)
*/
map<map_key, map_value> tree_based_map;
map<map_key, map_value>::const_iterator tree_based_map_it;
#if HAS_UNORDERED_MAP
unordered_map<map_key, map_value> hash_based_map;
unordered_map<map_key, map_value>::const_iterator hash_based_map_it;
#endif

/**
 * Set of characters from which keys are generated.
 * (used by function create_test_data)
*/
const char KEYCHARS[10+26+26] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'G', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' 
};

/**
 * Collection of all existing keys PLUS one not having an entry in the test data.
*/
vector<map_key> existing_keys;
vector<map_key> no_such_keys;
vector<map_key>::size_type key_select;

/**
 * Generate test data
*/
void create_test_data(const int nr_or_items, const int key_shared, const int key_min_len, const int key_max_len) {
	// temporary variable for the keys created.
	string some_key;
	// create common part shared by all keys
	while (some_key.size() < key_shared)
		some_key.append(KEYCHARS + rand() % (sizeof KEYCHARS), 1);
	// create variable part of first key
	while (some_key.size() < key_min_len)
		some_key.append(KEYCHARS + rand() % (sizeof KEYCHARS), 1);
	// fill known keys first, then unknown keys
	set<string> all_generated_keys;
	while (all_generated_keys.size() < 2*nr_or_items) {
		const vector<string>::size_type key_select = all_generated_keys.size();
		// create a key that not yet exists (latter is the reason for the outer loop)
		do {
			// cut off variable part of key
			some_key.resize(key_shared);
			// create new variable part
			const int key_len = key_min_len + (rand() % (1 + key_max_len - key_min_len));
			for (int i = key_shared; i < key_len; ++i)
				some_key.append(&KEYCHARS[rand() % (sizeof KEYCHARS)], 1);
		} while (all_generated_keys.insert(some_key).second == false);
		if (existing_keys.size() < nr_or_items) {
			assert(no_such_keys.size() == 0);
			// store as known key
			existing_keys.push_back(some_key);
			// insert into test-data
			const map_value some_value(key_select, 1.0/(key_select+1), some_key.substr(key_shared));
			tree_based_map.insert(make_pair(some_key, some_value));
			#if HAS_UNORDERED_MAP
			hash_based_map.insert(make_pair(some_key, some_value));
			#endif
		}
		else {
			assert(no_such_keys.size() < nr_or_items);
			// store as unknown key
			no_such_keys.push_back(some_key);
		}
	}
	// -----------------------------------------------------------------------------------------
	//                                                                 conditional sections only
	#if SHOW_TEST_DATA_CREATION
	cout << "created " << nr_or_items << " test data elements"
	     << " (changed with 1st cmd-line arg)" << endl;
	cout << "keys share an initial span of " << key_shared << " chars"
	     << " (changed with 2nd cmd-line arg)" << endl;
	cout << "keys have minimum length of " << key_min_len << " chars"
	     << " (changed with 3rd cmd-line arg)" << endl;
	cout << "keys have maximum length of " << key_max_len << " chars"
	     << " (changed with 4th cmd-line arg)" << endl;
	#endif
	#if SHOW_TEST_DATA_CONTENT
	cout << "tree-based map contains" << endl;
	for (vector<map_key>::const_iterator it = existing_keys.begin(); it != existing_keys.end(); ++it)
		assert(existing_keys.count(*it) == 1);
		assert(no_such_keys.count(*it) == 0);
		cout << "\t'" << *it << "' :"
		     << " { " << tree_based_map[*it].a << ", "
			      << tree_based_map[*it].b << ", "
			      << tree_based_map[*it].c
		     << " }" << endl;
	#if HAS_UNORDERED_MAP
	cout << "hash-based map contains" << endl;
	for (vector<map_key>::const_iterator it = existing_keys.begin(); it != existing_keys.end(); ++it) {
		assert(existing_keys.count(*it) == 1);
		assert(no_such_keys.count(*it) == 0);
		cout << "\t'" << *it << "' :"
		     << " { " << hash_based_map[*it].a << ", "
			      << hash_based_map[*it].b << ", "
			      << hash_based_map[*it].c
		     << " }" << endl;
	}
	#endif
	for (vector<map_key>::const_iterator it = no_such_keys.begin(); it != no_such_keys.end(); ++it) {
		assert(existing_keys.count(*it) == 0);
		assert(no_such_keys.count(*it) == 1);
		cout << "key '" << *it <<  "' is not contained in the test data" << endl;
	}
	#endif
	//
	// -----------------------------------------------------------------------------------------
}

#include "CXTIME.h"

struct map_key_cmp {
	const map_key& cmp;
	map_key_cmp(const map_key& _cmp) : cmp(_cmp) {}
	template<typename T>
	bool operator()(const T& e) const {
		return (cmp == e.first);
	}
};

int main(int argc, const char* argv[]) {

	// get test configuration details from command line arguments
	int n;
	const int test_data_size = (argc < 2 || (n = atoi(argv[1])) <= 0)
				? 50 : n;
	const int key_shared_len = (argc < 3 || (n = atoi(argv[2])) < 0)
				? 4 : n;
	const int key_min_len = (argc < 4 || (n = atoi(argv[3])) < key_shared_len+5)
				? key_shared_len+5 : n;
	const int key_max_len = (argc < 5 || (n = atoi(argv[4])) < key_min_len)
				? key_min_len : n;

	create_test_data(test_data_size, key_shared_len, key_min_len, key_max_len);

	key_select = 0;
	CXTIME("lookup random key contained in tree-based map with specific member 'find' (expect O(log(N))-performance)",
			const string& selected_key = existing_keys[key_select % existing_keys.size()];
		,
			tree_based_map_it = tree_based_map.find(selected_key);
		,
			assert(tree_based_map_it != tree_based_map.end());
			assert(tree_based_map_it->first == selected_key);
			assert(tree_based_map_it->second.a == key_select);
			assert(tree_based_map_it->second.b == static_cast<float>(1.0/(key_select+1)));
			assert(tree_based_map_it->second.c == selected_key.substr(key_shared_len));
		,
			++key_select;
	)

	key_select = 0;
	CXTIME("lookup key NOT contained in tree-based map with specific member 'find' (expect O(log(N))-performance)",
			const string& selected_key = no_such_keys[key_select % no_such_keys.size()];
		,
			tree_based_map_it = tree_based_map.find(selected_key);
		,
			assert(tree_based_map_it == tree_based_map.end());
		,
			++key_select;
	)
return 0;
	key_select = 0;
	CXTIME("lookup random key contained in tree-based map with generic algorithm 'find' (expect O(N)-performance)",
			const string& selected_key = existing_keys[key_select % existing_keys.size()];
		,
			tree_based_map_it = find_if(tree_based_map.begin(), tree_based_map.end(), map_key_cmp(selected_key));
		,
			assert(tree_based_map_it != tree_based_map.end());
			assert(tree_based_map_it->first == selected_key);
			assert(tree_based_map_it->second.a == key_select);
			assert(tree_based_map_it->second.b == static_cast<float>(1.0/(key_select+1)));
			assert(tree_based_map_it->second.c == selected_key.substr(key_shared_len));
		,
			++key_select;
	)

	key_select = 0;
	CXTIME("lookup key NOT contained in tree-based map with generic algorithm 'find' (expect O(N)-performance)",
			const string& selected_key = no_such_keys[key_select % no_such_keys.size()];
		,
			tree_based_map_it = find_if(tree_based_map.begin(), tree_based_map.end(), map_key_cmp(selected_key));
		,
			assert(tree_based_map_it == tree_based_map.end());
		,
			++key_select;
	)

#if HAS_UNORDERED_MAP
	key_select = 0;
	CXTIME("lookup random key contained in hash-based map with specific member 'find' (expect O(1)-performance)",
			const string& selected_key = existing_keys[key_select % existing_keys.size()];
		,
			hash_based_map_it = hash_based_map.find(selected_key);
		,
			assert(hash_based_map_it != hash_based_map.end());
			assert(hash_based_map_it->first == selected_key);
			assert(hash_based_map_it->second.a == key_select);
			assert(hash_based_map_it->second.b == static_cast<float>(1.0/(key_select+1)));
			assert(hash_based_map_it->second.c == selected_key.substr(key_shared_len));
		,
			++key_select;
	)

	key_select = 0;
	CXTIME("lookup key NOT contained in hash-based map with specific member 'find' (expect O(1)-performance)",
			const string& missing_key = no_such_keys[key_select % no_such_keys.size()];
		,
			hash_based_map_it = hash_based_map.find(missing_key);
		,
			assert(hash_based_map_it == hash_based_map.end());
		,
			++key_select;
	)

	key_select = 0;
	CXTIME("lookup random key contained in hash-based map with generic algorithm 'find' (expect O(N)-performance)",
			const string& selected_key = existing_keys[key_select % existing_keys.size()];
		,
			hash_based_map_it = find_if(hash_based_map.begin(), hash_based_map.end(), map_key_cmp(selected_key));
		,
			assert(hash_based_map_it != hash_based_map.end());
			assert(hash_based_map_it->first == selected_key);
			assert(hash_based_map_it->second.a == key_select);
			assert(hash_based_map_it->second.b == static_cast<float>(1.0/(key_select+1)));
			assert(hash_based_map_it->second.c == selected_key.substr(key_shared_len));
		,
			++key_select;
	)

	key_select = 0;
	CXTIME("lookup key NOT contained in hash-based map with generic algorithm 'find' (expect O(N)-performance)",
			const string selected_key = no_such_keys[key_select % no_such_keys.size()];
		,
			hash_based_map_it = find_if(hash_based_map.begin(), hash_based_map.end(), map_key_cmp(selected_key));
		,
			assert(hash_based_map_it == hash_based_map.end());
		,
			++key_select;
	)
#endif

}
