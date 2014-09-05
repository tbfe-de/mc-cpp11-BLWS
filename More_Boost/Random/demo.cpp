#include <boost/format.hpp>
#include <boost/random.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/unordered_map.hpp>
	using boost::unordered_map;
#include <map>
#include <iostream>
	using namespace std;

class Drawings {
	//typedef map<int, int> Map;
	typedef unordered_map<int, int> Map;
	const int probes;
	Map frequencies;
public:
	Drawings(int p)
		: probes(p)
	{
		Map tmp;

		boost::mt19937 rng;
		boost::variate_generator<
			boost::mt19937&, boost::uniform_int<>
		> rn(rng, boost::uniform_int<>(1, probes));

		for (int i= 0; i < probes; ++i)
			++tmp[rn()];

		frequencies.insert(make_pair(0, probes - tmp.size()));
		for (Map::iterator it(tmp.begin()); it != tmp.end(); ++it)
			++frequencies[it->second];
	}

	int probesize() const {
		return probes;
	}

	int count(int n) const {
		const Map::const_iterator f= frequencies.find(n);
		return (f == frequencies.end())
			? 0
			: f->second;
	}

	double percentage(int n) const {
		return 100.0 * static_cast<double>(count(n))
			     / static_cast<double>(probesize());
	}

	static void doDrawings(int from, int to, int probes, const string &output) {
		Drawings d(probes);
		for (int i= from; i <= to; ++i)
			cout << boost::format(output.c_str())
				% i
				% d.count(i)
				% d.probesize()
				% d.percentage(i);
	}

};

#include <boost/program_options/options_description.hpp>
	using boost::program_options::options_description;
	using boost::program_options::value;

#include <boost/program_options/variables_map.hpp>
	using boost::program_options::variables_map;
	using boost::program_options::notify;

#include <boost/program_options/parsers.hpp>
	using boost::program_options::parse_command_line;
	using boost::program_options::parse_environment;
	using boost::program_options::store;

static const char OUTFMT[]= "%4$8.5f %% %1$2d mal = %2$8d von %3$d";

bool parseOptions(const options_description &desc, int ac, char *av[], variables_map &vm) {
	try {
		store(parse_command_line(ac, av, desc), vm);
		store(parse_environment(desc, "DRAWINGS_"), vm);
		notify(vm);
		return true;
	}
	catch (boost::program_options::error &err) {
		cerr << err.what() << endl;
		return false;
	}
}

int main(int ac, char *av[]) {

	options_description visible("allowed options");
	visible.add_options()
		("help,H"	, "produce help message"	 	)
		("from,f"	, value<int>()->default_value(0)
				, "show from frequency"			)
		("to,t"		, value<int>()->default_value(9)
				, "show to frequency"			)
		("probes,P"	, value<int>()->default_value(10000)
				, "number of probes"			)
	;

	options_description hidden("hidden options");
	hidden.add_options()
		("outfmt"	, value<string>()->default_value(OUTFMT)
				, "output format"			)
	;

	variables_map vm;
	if (!parseOptions(visible.add(hidden), ac, av, vm)) {
		cerr << visible << endl;
		return 1;
	}
	Drawings::doDrawings(
		vm["from"].as<int>(),
		vm["to"].as<int>(),
		vm["probes"].as<int>(),
		vm["outfmt"].as<string>() + "\n"
	);

}
