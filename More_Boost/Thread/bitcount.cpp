#include <algorithm>
	using std::generate_n;
#include <cstddef>
	using std::size_t;
#include <cstdlib>
	using std::atol;
	using std::rand;
#include <cstring>
	using std::strcmp;
#include <vector>
	using std::vector;

#define SZ (100*1000*1000UL)


#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <functional>
	using std::function;
#include <thread>
	using std::move;
	using std::packaged_task;
	using std::thread;
	using std::unique_future;
#else
#include <boost/function.hpp>
	using boost::function;
#include <boost/thread.hpp>
	using boost::move;
	using boost::packaged_task;
	using boost::thread;
	using boost::unique_future;
#endif

void fillMemory(vector<unsigned char> &bytes)
{
	generate_n(bytes.begin(), bytes.size(), rand);
}

inline
int bits_shift(unsigned char byte) {
	int count= 0;
	while (byte) {
		count += (byte & 0x1);
		byte >>= 1;
	}
	return count;
}

inline
int bits_lookup(unsigned char byte) {
	static const int bits[256] = {
		0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8,
	};
	/*
		awk 'BEGIN {
			for (i= 0; i < 256;) {
				c= 0; b= i;
				while (b) {
					if (b % 2) ++c
					b = int(b/2);
				}
				printf "%d,%s", c, (++i % 16 ? "" : "\n");
			}
		}' /dev/null
	*/
	return bits[byte];
}

inline
unsigned long bitCount(const unsigned char bytes[], size_t size, function<int(unsigned char)> f)
{
	unsigned long count= 0;
	for (size_t i= 0; i < size; ++i)
		count += f(bytes[i]);
	return count;
}

struct BitCounter {
	BitCounter(const unsigned char *_byte, size_t _size, function<int(unsigned char)> _cntf)
		: byte(_byte), size(_size), cntf(_cntf)
	{}
	unsigned long operator()() {
		return bitCount(byte, size, cntf);
	}
private:
	const unsigned char *byte;
	size_t size;
	function<int(unsigned char)> cntf;
};

unsigned long bitCount_mt(const unsigned char byte[], size_t size,
			  int nthreads, function<int(unsigned char)> f) {
	size_t psize= size / nthreads;
	BitCounter **workers = new BitCounter*[nthreads];
	packaged_task<unsigned long> **tasks = new packaged_task<unsigned long>*[nthreads];
	unique_future<unsigned long> **futures = new unique_future<unsigned long>*[nthreads];
	for (int i= 0; i < nthreads; ++i) {
		const size_t nbytes= (i < nthreads-1)
					? psize
					: (size - (nthreads-1)*psize);
		workers[i]= new BitCounter(&byte[i*psize], nbytes, f);
		tasks[i]= new packaged_task<unsigned long>(*workers[i]);
		futures[i]= new unique_future<unsigned long>(tasks[i]->get_future());
		thread(move(*tasks[i]));
	}
	unsigned long count= 0;
	for (int i= 0; i < nthreads; ++i) {
		count += futures[i]->get();
		delete futures[i];
		delete tasks[i];
		delete workers[i];
	}
	delete[] futures;
	delete[] tasks;
	delete[] workers;
	return count;
}

#include <iostream>
	using std::cerr;
	using std::cout;
	using std::endl;

int main(int argc, char *argv[]) {
	if (3 <= argc && argc <= 4) {
		int nbytes= atoi(argv[2]);
		if (nbytes <= 0) {
			cerr << "bitcount: nbytes must be greater than zero\n";
			return EXIT_FAILURE;
		}
		int nthreads= (argc > 3) ? atoi(argv[3]) : 0;
		if (nthreads < 0) {
			cerr << "bitcount: nthreads must not be less than zero\n";
			return EXIT_FAILURE;
		}
		
		vector<unsigned char> space(atol(argv[2]));
		fillMemory(space);

		if (strcmp(argv[1], "shift") == 0) {
			if (nthreads == 0)
				cout << bitCount(&space[0], space.size(), bits_shift);
			else
				cout << bitCount_mt(&space[0], space.size(), nthreads, bits_shift);
			cout << endl;
			return EXIT_SUCCESS;
		}
		if (strcmp(argv[1], "lookup") == 0) {
			if (nthreads == 0)
				cout << bitCount(&space[0], space.size(), bits_lookup);
			else
				cout << bitCount_mt(&space[0], space.size(), nthreads, bits_lookup);
			cout << endl;
			return EXIT_SUCCESS;
		}
	}
	cerr << "Usage: bitcount [shift|lookup] nbytes [nthreads]\n";
	return EXIT_FAILURE;
}
