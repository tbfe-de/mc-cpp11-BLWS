#include <boost/program_options.hpp>

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	namespace po = boost::program_options;

	po::options_description desc("Allowed Options");
	desc.add_options()
		("help,h", "produce help message")
		("compress,c", po::value<int>(), "set compression level")
	;

	po::variables_map vm;
	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (po::unknown_option &ex) {
		cout << ex.what() << "\n(use --help to show usage)" << endl;
		return 1;
	}
	catch (po::invalid_option_value &ex) {
		cout << ex.what() << endl;
		return 1;
	}
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return 0;
	}

	if (vm.count("compress")) {
		cout << "compression level set to "
		     << vm["compress"].as<int>() << endl;
	}
	else {
		cout << "compression level not set" << endl;
	}
}
