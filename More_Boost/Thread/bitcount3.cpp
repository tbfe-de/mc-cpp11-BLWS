#include <algorithm>
	using std::generate_n;
#include <cstddef>
	using std::size_t;
#include <cstdlib>
	using std::atol;
	using std::rand;
#include <ctime>
	using std::clock;
	using std::clock_t;
#include <cstring>
	using std::strcmp;
#include <string>
	using std::string;
#include <vector>
	using std::vector;

#define SZ (100*1000*1000UL)

#include <boost/function.hpp>
	using boost::function;

#include <boost/program_options.hpp>
	using boost::program_options::options_description;
	using boost::program_options::value;
	using boost::program_options::variables_map;

#include "../Forked/Forked.h"

void fillMemory(vector<unsigned char> &bytes)
{
	generate_n(bytes.begin(), bytes.size(), rand);
}

struct bits_shift {
	static
	int count(unsigned char byte) {
		int result= 0;
		while (byte) {
			result += (byte & 0x1);
			byte >>= 1;
		}
		return result;
	}
};

struct bits_lookup {
	static
	int count(unsigned char byte) {
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
};

template<typename BitsPerByte>
unsigned long bitCount(const unsigned char bytes[], const size_t size)
{
	unsigned long count= 0;
	for (size_t i= 0; i < size; ++i)
		count += BitsPerByte::count(bytes[i]);
	return count;
}

struct CountStart {
	const int nworkers;
	const unsigned char* addr;
	const size_t size;
	CountStart(const int nworkers_, const unsigned char* addr_, const size_t size_)
		: nworkers(nworkers_), addr(addr_), size(size_)
	{}
};

struct CountTask {
	const int id;
	const unsigned char* const addr;
	const size_t size;
	CountTask(const int id_, const unsigned char* const addr_, const size_t size_)
		: id(id_), addr(addr_), size(size_)
	{}
};

struct CountResult {
	const int id;
	const unsigned long bits;
	CountResult(const int id_, const unsigned long bits_)
		: id(id_), bits(bits_)
	{}
};

template<typename BitsPerByte>
struct BitCounter;

template<typename BitsPerByte>
struct DistributedCounter {
	static void receive(CountStart& start);
	static void receive(CountResult& result);
private:
	static clock_t tstamp;
	static int nworkers;
	static Forked::Link<BitCounter<BitsPerByte>, DistributedCounter<BitsPerByte> > **workers;
	static unsigned long count;
};

template<class BitsPerByte>
clock_t DistributedCounter<BitsPerByte>::tstamp;

template<typename BitsPerByte>
struct BitCounter {
	typedef Forked::Link<BitCounter<BitsPerByte>, DistributedCounter<BitsPerByte> > Link;
	static void receive(CountTask& region);
};

template<typename BitsPerByte>
void BitCounter<BitsPerByte>::receive(CountTask& region) {
	const unsigned long cnt(
		bitCount<BitsPerByte>(region.addr, region.size)
	);
	Link::parent.template send<CountResult>(region.id, cnt);
}

template<class BitsPerByte>
int DistributedCounter<BitsPerByte>::nworkers = 0;

template<class BitsPerByte>
Forked::Link<BitCounter<BitsPerByte>, DistributedCounter<BitsPerByte> >
**DistributedCounter<BitsPerByte>::workers = 0;

template<class BitsPerByte>
unsigned long DistributedCounter<BitsPerByte>::count = 0uL;

template<class BitsPerByte>
void DistributedCounter<BitsPerByte>::receive(CountStart& start) {
	tstamp = clock();
	FORKED_ASSERT(nworkers == 0);
	FORKED_ASSERT(workers == 0);
	nworkers = start.nworkers;
	FORKED_TRACE(Notice) << "starting " << nworkers << " workers";
	const size_t psize= start.size / nworkers;
	static const char name[] = "BC";
	workers = new typename BitCounter<BitsPerByte>::Link*[nworkers];
	for (int i= 0; i < nworkers; ++i) {
		workers[i] = new Forked::Link< BitCounter<BitsPerByte>, DistributedCounter<BitsPerByte> >(name);
		const size_t nbytes= (i < nworkers-1)
					? psize
					: (start.size - (nworkers-1)*psize);
		FORKED_TRACE(Notice) << "process " << (i+1);
		workers[i]->spawn().template send<CountTask>(i, start.addr + (i*psize), nbytes);
	}
}

template<class BitsPerByte>
void DistributedCounter<BitsPerByte>::receive(CountResult& result) {
	FORKED_ASSERT(nworkers > 0);
	FORKED_ASSERT(result.id >= 0);
	FORKED_ASSERT(result.id < nworkers);
	FORKED_ASSERT(workers != 0);
	FORKED_ASSERT(workers[result.id] != 0);

	FORKED_TRACE(Notice) << "thread " << (result.id+1) << " done";

	count += result.bits;
	//workers[result.id].send<Forked::Exit>(0);
	delete workers[result.id];
	workers[result.id] = 0;
	for (int i = 0; i < nworkers; ++i) {
		if (workers[i] != 0) {
			return;
		}
	}
	FORKED_TRACE(Notice) << "completion";
	delete[] workers;
	workers = 0;
	nworkers = 0;
	tstamp = clock() - tstamp;
	FORKED_TRACE(Print) << count << " (" << 1e6*static_cast<float>(tstamp)/CLOCKS_PER_SEC << " usec)\n";
	
	Forked::exit(0);
}

#include <iostream>
	using std::cerr;
	using std::cout;
	using std::endl;

namespace Forked {

	Readonly_NAME NAME = "DCNT";

	int main(int argc, char *argv[]) {
		boost::program_options::options_description cmdLineOptions("Supported Options");
		cmdLineOptions.add_options()
			("help,h", "show and describe options")
			("file,f", value<string>(), "name of file to process")
		;

		variables_map optionVariables;
		store(parse_command_line(argc, argv, cmdLineOptions), optionVariables);
		notify(optionVariables);    

		if (optionVariables.count("help")) {
			cout << cmdLineOptions << "\n";
			return EXIT_FAILURE;
		}

		if (optionVariables.count("file")) {
			cout << "input file is " << optionVariables["file"].as<string>() << '\n';
		}
return EXIT_SUCCESS;

		if (argc < 3 || argc > 4) {
			cerr << "Usage: bitcount [shift|lookup] nbytes [nworkers]\n";
			return EXIT_FAILURE;
		}
		int nbytes= atoi(argv[2]);
		if (nbytes <= 0) {
			cerr << "bitcount: nbytes must be greater than zero\n";
			return EXIT_FAILURE;
		}
		int nworkers= (argc > 3) ? atoi(argv[3]) : 0;
		if (nworkers < 0) {
			cerr << "bitcount: nworkers must not be less than zero\n";
			return EXIT_FAILURE;
		}
		
		FORKED_TRACE(Notice) << "starting up";
		vector<unsigned char> space(atol(argv[2]));
		fillMemory(space);

		if (strcmp(argv[1], "shift") == 0) {
			if (nworkers == 0) {
				//cout << bitCount<bits_shift>(&space[0], static_cast<size_t>(space.size())) << endl;
				return EXIT_SUCCESS;
			}
			else {
				Forked::Link< DistributedCounter<bits_shift> > dc_shift("S");
				dc_shift.spawn().send<CountStart>(
					nworkers, &space[0], space.size()
				);
			}
		}
		if (strcmp(argv[1], "lookup") == 0) {
			if (nworkers == 0) {
				//cout << bitCount<bits_lookup>(&space[0], static_cast<size_t>(space.size())) << endl;
				return EXIT_SUCCESS;
			}
			else {
				Forked::Link< DistributedCounter<bits_shift> > dc_lookup("L");
				dc_lookup.spawn().send<CountStart>(
					nworkers, &space[0], space.size()
				);
			}
		}
	}
}
