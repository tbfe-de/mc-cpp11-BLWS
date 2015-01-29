//! Quicksort inmplementation for C-Array (compatible)

#ifndef QUICKSORT_RUNS
#define QUICKSORT_RUNS 5
#endif

#ifndef DATASET_SIZE
#define DATASET_SIZE 100
#endif

#ifndef DATASET_ELEMTYPE
#define DATASET_ELEMTYPE double
#endif

#ifndef DATASET_CONTAINER
#define DATASET_CONTAINER std::array
#endif

#ifndef DATASET_PREALLOC
#define DATASET_PREALLOC 1
#endif

#ifndef QUICKSORT_THREADS
#define QUICKSORT_THREADS 0
#endif

#ifndef QUICKSORT_CONCURRENT
#define QUICKSORT_CONCURRENT 0
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <deque>
#include <future>
#include <iostream>
#include <iterator>
#include <vector>

#if DATASET_PREALLOC
typedef DATASET_CONTAINER<DATASET_ELEMTYPE, DATASET_SIZE> DataSetType;
#else
typedef DATASET_CONTAINER<DATASET_ELEMTYPE> DataSetType;
#endif
typedef DataSetType::value_type DataSetValueType;

inline
void swap(DataSetType::iterator xp, DataSetType::iterator yp) {
    auto t = *xp; *xp = *yp; *yp = t;
}

DataSetType::iterator partition(DataSetType::iterator leftp, DataSetType::iterator rightp) {
   const auto pivot = *leftp;
   auto lp = leftp;
   auto rp = rightp;
   for (;;) {
   	do ++lp; while (*lp <= pivot && lp+1 <= rightp);
   	do --rp; while (*rp > pivot);
   	if (lp >= rp) {
	    swap(leftp, rp);
	    return rp;
	}
	swap(lp, rp);
   }
}

void quicksort(DataSetType::iterator leftp, DataSetType::iterator rightp) {
    if (leftp+1 < rightp) {
        // divide and conquer
	const auto pp = partition(leftp, rightp);
#if	QUICKSORT_CONCURRENT
        auto sl = std::async(quicksort, leftp, pp);
        auto sr = std::async(quicksort, pp+1, rightp);
	sl.get();
	sr.get();
#else
        quicksort(leftp, pp);
        quicksort(pp+1, rightp);
#endif
    }
}


#if DATASET_SIZE > 10
inline
void showarray(const char* txt, DataSetType::const_iterator beg, DataSetType::const_iterator end) {}
#else
void showarray(const char* txt, DataSetType::const_iterator beg, DataSetType::const_iterator end) {
    using std::copy_n;
    using std::cout;

    cout << txt << ':';
    while (beg < end)
        cout << ' ' << *beg++;
    cout << '\n';
}
#endif

DataSetType testData;

#if DATASET_PREALLOC
void allocateTestData() {}
#else
void allocateTestData() {
    testData.resize(DATASET_SIZE);
}
#endif

void prepareTestData() {
    allocateTestData();
    const auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < testData.size(); ++i)
	testData[i] = std::sqrt(rand());
    const auto end = std::chrono::high_resolution_clock::now();
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    std::cout << "set up initial test data in "
              << duration_cast<microseconds>(end-start).count() << " msec\n";
}

void sortPerformance() {
    auto start = std::chrono::steady_clock::now();
    for (auto i = 0; i < QUICKSORT_RUNS; ++i) {
//  	const auto lap = std::chrono::steady_clock::now();
//      assert(std::is_sorted(testData.begin(), testData.end()));
//	std::random_shuffle(testData.begin(), testData.end());
//	start += (std::chrono::steady_clock::now() - lap);
	const auto beg = testData.begin();
	const auto end = testData.end();
#if	QUICKSORT_THREADS > 3
	const auto split1 = beg + (end - beg) / 4;
	const auto split2 = split1 + (end - split1) / 3;
	const auto split3 = split2 + (end - split2) / 2;
	auto sort1 = std::async(quicksort, beg, split1);
	std::cout << '1' << std::flush;
	auto sort2 = std::async(quicksort, split1, split2);
	std::cout << '2' << std::flush;
	auto sort3 = std::async(quicksort, split2, split3);
	std::cout << '3' << std::flush;
	auto sort4 = std::async(quicksort, split3, end);
	std::cout << '4' << std::flush;
	sort1.get();
	sort2.get();
	sort3.get();
	sort4.get();
	auto merge1 = std::async([=] { std::inplace_merge(beg, split1, split2); });
	std::cout << 'A' << std::flush;
	auto merge2 = std::async([=] { std::inplace_merge(split2, split3, end); });
	std::cout << 'B' << std::flush;
	merge1.get();
	merge2.get();
	std::cout << '*' << std::flush;
	std::inplace_merge(beg, split2, end);
#elif	QUICKSORT_THREADS == 3
	const auto split1 = beg + (end - beg) / 3;
	const auto split2 = split1 + (end - split1) / 2;
	auto sort1 = std::async(quicksort, beg, split1);
	std::cout << '1' << std::flush;
	auto sort2 = std::async(quicksort, split1, split2);
	std::cout << '2' << std::flush;
	auto sort3 = std::async(quicksort, split2, end);
	std::cout << '3' << std::flush;
	sort1.get();
	sort2.get();
	sort3.get();
	std::cout << '*' << std::flush;
	std::inplace_merge(beg, split1, split2);
	std::inplace_merge(beg, split2, end);
#elif	QUICKSORT_THREADS == 2
	auto split = beg + (end - beg) / 2;
	auto sort1 = std::async(quicksort, beg, split);
	std::cout << '1' << std::flush;
	auto sort2 = std::async(quicksort, split, end);
	std::cout << '2' << std::flush;
	sort1.get();
	sort2.get();
	std::cout << '*' << std::flush;
	std::inplace_merge(beg, split, end);
#else
	std::cout << '*' << std::flush;
	quicksort(beg, end);
#endif
    }
    std::cout << '\n';
    const auto end = std::chrono::steady_clock::now();
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::microseconds;
    const auto msec_total = duration_cast<milliseconds>(end-start).count();
    const auto usec_per_run = duration_cast<microseconds>(end-start).count()
		            / static_cast<double>(QUICKSORT_RUNS);
    std::cout << "total time for " << QUICKSORT_RUNS << " runs "
              << msec_total << " msec" << " (" << usec_per_run << " usec per run)\n";
}


int main() {

    prepareTestData();

    showarray("unsorted", testData.cbegin(), testData.cend());
    quicksort(testData.begin(), testData.end());
    showarray("sorted", testData.cbegin(), testData.cend());

    sortPerformance();

}
