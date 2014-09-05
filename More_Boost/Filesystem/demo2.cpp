#include "Util/CK/CK.h"

#include <boost/filesystem.hpp>
	namespace fs = boost::filesystem;

int main() {
/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path construction (empty) ............."			)
/////////////////////////////////////////////////////////////////////////////////
		const fs::path p0;
CK_compare(	p0.empty()			, true				)
CK_compare(	p0.string()			, ""				)

/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path construction (portable grammar) .."			)
/////////////////////////////////////////////////////////////////////////////////
		const fs::path p1("/whatever/foo/bar/ba.z");
CK_compare(	p1.empty()			, false				)
CK_compare(	p1.string()			, "/whatever/foo/bar/ba.z"	)
//CK_compare(	p1.native()  	 		, "\\whatever\\foo\\bar\\ba.z"	)
CK_compare(	p1.native()  	 		, "/whatever/foo/bar/ba.z"	)
CK_compare(	p1.root_directory()		, "/"				)
CK_compare(	p1.filename()			, "ba.z"			)
CK_compare(	p1.stem()			, "ba"		 		)
CK_compare(	p1.extension()			, ".z"				)
		
/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path construction (native) ............"			)
/////////////////////////////////////////////////////////////////////////////////
//		const fs::path p2("\\whatever\\foo\\bar\\ba.z");
		const fs::path p2("/whatever/foo/bar/ba.z");
CK_compare(	p2.empty()			, false				)
CK_compare(	p2.string()			, "/whatever/foo/bar/ba.z"	)

/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path construction (by operator/) ......"			)
/////////////////////////////////////////////////////////////////////////////////
		fs::path p3("/cygdrive");
		p3 /= fs::path("c") / fs::path("foo") / fs::path("bar");
CK_compare(	p3.string()			, "/cygdrive/c/foo/bar"		)

/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path assignment ......................."			)
/////////////////////////////////////////////////////////////////////////////////
		fs::path p4;
CK_compare(	p3.string()			, "/cygdrive/c/foo/bar"		)
CK_compare(	p4.string()			, ""				)
		p3.swap(p4);
CK_compare(	p3.string()			, ""				)
CK_compare(	p4.string()			, "/cygdrive/c/foo/bar"		)
		p3 = p4.parent_path();
CK_compare(	p3.string()			, "/cygdrive/c/foo"		)
CK_compare(	p4.string()			, "/cygdrive/c/foo/bar"		)
CK_compare(	fs::equivalent(p3, p4)		, false				)
		p3 /= "..";
CK_compare(	p3.string()			, "/cygdrive/c/foo/.."		)
CK_compare(	fs::equivalent(p3, p4)		, false				)
		p3 /= "foo/bar";
CK_compare(	p3.string()			, "/cygdrive/c/foo/../foo/bar"	)
CK_compare(	p4.string()			, "/cygdrive/c/foo/bar"		)
CK_compare(	fs::equivalent(p3, p4)		, true				)

/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path iteration  ......................."			)
/////////////////////////////////////////////////////////////////////////////////
CK_compare(	p4.string()			, "/cygdrive/c/foo/bar"		)
		fs::path::iterator it = p4.begin();
CK_compare(	*it		 		, "/"				)
CK_compare(	*++it		 		, "cygdrive"			)
CK_compare(	*++it		 		, "c"				)
CK_compare(	*++it		 		, "foo"				)
CK_compare(	*++it		 		, "bar"				)
CK_compare(	++it == p4.end()		, true				)
		p4 = "cygdrive/c/foo/bar";
CK_compare(	p4.string()			, "cygdrive/c/foo/bar"		)
		it = p4.begin();
CK_compare(	*it		 		, "cygdrive"			)
CK_compare(	*++it		 		, "c"				)
CK_compare(	*++it		 		, "foo"				)
CK_compare(	*++it		 		, "bar"				)
CK_compare(	++it == p4.end()		, true				)

/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Path modification ....................."			)
/////////////////////////////////////////////////////////////////////////////////
                p4 = "/cygdrive/c/foo/bar"; // same as p4 = fs::path(...);
CK_compare(	p4.string()			, "/cygdrive/c/foo/bar"		)
		p4.remove_filename() /= "ba.z";
CK_compare(	p4.string()			, "/cygdrive/c/foo/ba.z"	)
		p4.replace_extension("y");
CK_compare(	p4.string()			, "/cygdrive/c/foo/ba"	)
		p4.remove_filename();
CK_compare(	p4.string()			, "/cygdrive/c/foo"		)
		p4.remove_filename();
CK_compare(	p4.string()			, "/cygdrive/c"			)
		p4.remove_filename();
CK_compare(	p4.string()			, "/cygdrive"			)
		p4.remove_filename();
CK_compare(	p4.string()			, "/"				)
		p4.remove_filename();
CK_compare(	p4.string()			, ""				)
		p4.remove_filename();
CK_compare(	p4.string()			, ""				)

/////////////////////////////////////////////////////////////////////////////////
CK_section(	"Directory creation and deletion ......."			)
/////////////////////////////////////////////////////////////////////////////////
		fs::path p5("newdir");
		fs::path p6(p5 / "subd");  // same as: p6(p5 / fs::path("subd"))
		static_cast<void>(
			// in case directories still
			// exist from previous tests
			//
			fs::remove(p6), fs::remove(p5)
		);
CK_compare(	fs::exists(p5)			, false				)
CK_compare(	fs::create_directory(p5)	, true				)
CK_compare(	fs::exists(p5)			, true 				)
CK_compare(	fs::is_directory(p5)		, true 				)
CK_compare(	fs::create_directory(p6)	, true				)
CK_compare(	fs::remove(p5)			, false				)
CK_compare(	fs::remove(p6)			, true 				)
CK_compare(	fs::remove(p5)			, true				)

}

