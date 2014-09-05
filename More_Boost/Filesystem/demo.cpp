#include "Util/CK/CK.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace boost::filesystem;

bool find_file(const path & dir_path,         // in this directory,
               const std::string & file_name, // search for this name,
               path & path_found )            // placing path here if found
{
	if (!exists(dir_path)) 
		return false;
	directory_iterator end_itr; // default construction yields past-the-end
	for (directory_iterator itr(dir_path); itr != end_itr; ++itr) {
		if (path(*itr).leaf() == file_name) {
			path_found = itr->path();
			return true;
		}
		if (is_directory(itr->status())) {
			if (find_file(itr->path(), file_name, path_found))
				return true;
		}
	}
	return false;
}

#include <string>
	using std::string;

int main() {
		const string tdir("deleted-after-test");
		remove_all(tdir);
CK_section(	"Create directories ...................."		)
CK_compare(	is_directory(tdir)			, false		)
		create_directory(tdir);
		const path sub(tdir / path("sub"));
CK_compare(	is_directory(sub)			, false		)
		create_directory(sub);
		const path sub_sub2(sub / path("sub2"));
CK_compare(	is_directory(sub_sub2)			, false		)
		create_directory(sub_sub2);

CK_section(	"Testing directories and files ........."		)
CK_compare(	is_directory(tdir)			, true		)
CK_compare(	is_directory(sub)			, true		)
CK_compare(	is_directory(sub_sub2)			, true		)
CK_compare(	is_regular(sub_sub2 / "file1")		, false		)
		ofstream f(sub_sub2 / "file1");
CK_compare(	is_regular(sub_sub2 / "file1")		, true		)
CK_compare(	is_directory(sub_sub2 / "file1")	, false		)
CK_compare(	is_regular(sub_sub2 / "file2")		, false		)

CK_section(	"Finding directories and files ........."		)
		path fname;
CK_compare(	find_file(".", "file1", fname) 		, true		)
CK_compare(	fname		, "./deleted-after-test/sub/sub2/file1"	)
CK_compare(	find_file(tdir, "file1", fname) 	, true		)
CK_compare(	fname		, "deleted-after-test/sub/sub2/file1"	)
CK_compare(	find_file(".", "sub2", fname) 		, true		)
CK_compare(	fname		, "./deleted-after-test/sub/sub2"	)
CK_compare(	find_file(".", "file2", fname)		, false		)
}

