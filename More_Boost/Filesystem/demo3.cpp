#include "Util/CK/CK.h"

#include <cstdlib>
	// using EXIT_FAILURE (macro)

#include <iostream>
	using std::cerr;
	using std::cout;
	using std::endl;

#include <iomanip>
	using std::setw;

#include <boost/filesystem.hpp>
	namespace fs = boost::filesystem;

void showfiles(fs::recursive_directory_iterator it) {
	fs::recursive_directory_iterator dummy;
	while (it != dummy) {
		const int indent(4 * it.level());
		cout << setw(indent) << ""
		     << it->filename() << (fs::is_directory(*it) ? "/" : "")
		     << endl;
		++it;
	}
}

int main(int argc, const char* argv[]) {
	const fs::path startdir(
		(argc == 1)
			? fs::current_path()
			: fs::path(argv[1])
	);
	if (!fs::is_directory(startdir)) {
		cerr << "not a directory: " << startdir.string() << endl;
		return EXIT_FAILURE;
	}
	showfiles(fs::recursive_directory_iterator(startdir));
}
