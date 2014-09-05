#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

#include "boost/array.hpp"
#include "boost/multi_array.hpp"

#include "Util/CK/CK.h"

int main() {
	typedef boost::multi_array<char, 2> Matrix;
	typedef boost::multi_array<int, 3> Array3D;
	{ // ==  Create empty multi-arrays
		Matrix m;
		Array3D d;
CK_section(	"Multi-Arrays created empty ............"	)
CK_compare(	m.dimensionality,			2	)
CK_compare(	d.shape()[0],				0	)
CK_compare(	d.shape()[1],				0	)
CK_compare(	d.dimensionality,			3	)
CK_compare(	d.shape()[0],				0	)
CK_compare(	d.shape()[1],				0	)
CK_compare(	d.shape()[2],				0	)
	}
	{ // == Create sized multi-arrays
		Matrix m(boost::extents[10][15]);
		Array3D d(boost::extents[3][4][2]);
CK_section(	"Multi-Arrays created with given size .."	)
CK_compare(	m.dimensionality,			2	)
CK_compare(	m.shape()[0],				10	)
CK_compare(	m.shape()[1],				15	)
CK_compare(	d.dimensionality,			3	)
CK_compare(	d.shape()[0],				3	)
CK_compare(	d.shape()[1],				4	)
CK_compare(	d.shape()[2],				2	)
	  // ==	Access multi-arrays
CK_section(	"Multi-Arrays accessing ................"	)
		boost::array<size_t, 2> x12 = {{ 1, 2 }};
		m[1][2] = 'a';
CK_compare(	m(x12),					'a'	)
		boost::array<size_t, 2> x79 = {{ 7, 9 }};
		m(x79) = 'z';
CK_compare(	m[7][9],				'z'	)
CK_section(	"Multi-Arrays slicing .................."	)
	}
	typedef boost::const_multi_array_ref<double, 2> M23;
	{
		static const double rawdata[6] = {
			1.1 , 1.2 , 1.3,
			2.1 , 2.2 , 2.3
		};
		M23 d(rawdata, boost::extents[2][3]);
CK_compare(	d[0][0],				1.1	)
CK_compare(	d[0][1],				1.2	)
CK_compare(	d[0][2],				1.3	)
CK_compare(	d[1][0],				2.1	)
CK_compare(	d[1][1],				2.2	)
CK_compare(	d[1][2],				2.3	)
	}

}
