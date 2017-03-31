/*
 ==============================================================================
 What output may the following program generate?
 ==============================================================================
*/

#include <atomic>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

std::atomic_int counter{0};

void uptick(int n) {
	while (n-- > 0) {
	    int local = counter;
	    counter = ++local;
	}
}

int main() {
	auto f1 = std::async(std::launch::async, []() {uptick(5);});
	auto f2 = std::async(std::launch::async, []() {uptick(3);});
	f1.get();
	f2.get();
	std::cout << "final counter = " << counter << std::endl;
	//
	// What possibilities exist for the final value of counter?
	// at least: [ ] = 1, [ ] = 2, [ ] = 3, [ ] = 5, [ ] = 8
	// at most : [ ] = 2, [ ] = 3, [ ] = 5, [ ] = 8, [ ] = 10
}
