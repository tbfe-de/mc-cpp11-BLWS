struct nullary1 {
	typedef int type;
};

struct nullary2 {
	typedef double type;
};

template<class T>
struct add_pointer {
	typedef T* type;
};

template<class T>
struct remove_pointer;

template<class T>
struct remove_pointer<T *> {
	typedef T type;
};

template<bool b, class T1, class T2>
struct T1_or_T2;

template<class T1, class T2>
struct T1_or_T2<true, T1, T2> {
	typedef T1 type;
};

template<class T1, class T2>
struct T1_or_T2<false, T1, T2> {
	typedef T2 type;
};

struct false_type {
	static const bool value= false;
};

struct true_type {
	static const bool value= true;
};

template<class T_cond, class T_true, class T_false>
struct if_;

template<class T_true, class T_false>
struct if_<true_type, T_true, T_false> {
	typedef T_true type;
};

template<class T_true, class T_false>
struct if_<false_type, T_true, T_false> {
	typedef T_false type;
};

template<class T1, class T2>
struct compare_types {
	typedef false_type type;
};

template<class T>
struct compare_types<T, T> {
	typedef true_type type;
};

template<class T>
struct remove_all_pointer {
	typedef T type;
};

template<class T>
struct remove_all_pointer<T *> {
	typedef typename remove_all_pointer<T>::type type;
};


class MyClass {};
class YourClass {};

template<bool, class T_true, class T_false>
struct if_c;

template<class T_true, class T_false>
struct if_c<true, T_true, T_false> : if_<true_type, T_true, T_false> {};

template<class T_true, class T_false>
struct if_c<false, T_true, T_false> : if_<false_type, T_true, T_false> {};

template<int val>
struct int_ {
	static const int value= val;
};

template<int N>
struct faculty {
	static const int value= N * faculty<N-1>::value;
	typedef int_<value> type;
};

template<>
struct faculty<1> {
	static const int value= 1;
	typedef int_<value> type;
};


#include "Util/CK/CK.h"

int main() {
#if 0
CK_section(	"Nullary functions ....................."				)
CK_compare(	typeid(nullary1::type)				, typeid(int)		)
CK_compare(	typeid(nullary2::type)				, typeid(double)	)

CK_section(	"Basic type mappings ..................."				)
CK_compare(	typeid(nullary2::type)				, typeid(double)	)
CK_compare(	typeid(add_pointer<int>::type)			, typeid(int *)		)
CK_compare(	typeid(add_pointer<double>::type)		, typeid(double *)	)
CK_compare(	typeid(remove_pointer<int *>::type)		, typeid(int)		)
CK_compare(	typeid(remove_pointer<double *>::type)		, typeid(double)	)

CK_section(	"Advanced mappings ....................."				)
CK_compare(	typeid(remove_all_pointer<double *>::type)	, typeid(double)	)
CK_compare(	typeid(remove_all_pointer<double **>::type)	, typeid(double)	)
CK_compare(	typeid(remove_all_pointer<double ***>::type)	, typeid(double)	)
CK_compare(	typeid(remove_all_pointer<double ****>::type)	, typeid(double)	)

CK_section(	"Making decisisions ...................."				)
CK_compare(	typeid(T1_or_T2<true, int, int *>::type)	, typeid(int)		)
CK_compare(	typeid(T1_or_T2<false, int, int *>::type)	, typeid(int *)		)
CK_compare(	typeid(if_<true_type, int, int *>::type)	, typeid(int)		)
CK_compare(	typeid(if_<false_type, int, int *>::type)	, typeid(int *)		)

CK_section(	"Comparing types ......................."				)
CK_compare(	typeid(compare_types<int, int>::type)		, typeid(true_type)	)
CK_compare(	typeid(compare_types<int, int *>::type)		, typeid(false_type)	)
CK_compare(	typeid(compare_types<int, double>::type)	, typeid(false_type)	)

CK_section(	"Nested calls .........................."				)
CK_compare(	typeid(compare_types<
			int, remove_pointer<int *>::type
		>::type)					, typeid(true_type)	)
CK_compare(	typeid(compare_types<
			int, remove_pointer<int **>::type
		>::type)					, typeid(false_type)	)
CK_compare(	typeid(compare_types<
			int, remove_all_pointer<int ***>::type
		>::type)					, typeid(true_type)	)
CK_compare(	typeid(T1_or_T2<
			compare_types<int, int>::type::value,
			MyClass,
			YourClass
		>::type)					, typeid(MyClass)	)
CK_compare(	typeid(T1_or_T2<
			compare_types<int, double>::type::value,
			MyClass,
			YourClass
		>::type)					, typeid(YourClass)	)
#endif
CK_section(	"Faculty calculation ..................."				)
		int res;
//CK_compare(	typeid(faculty<1>::type)			, typeid(int_<1>)	)
CK_compare(	res= faculty<1>::value				, 1			)
CK_compare(	res= faculty<2>::value				, 2			)
CK_compare(	res= faculty<3>::value				, 6			)
CK_compare(	res= faculty<4>::value				, 24			)
CK_compare(	res= faculty<5>::value				, 120			)
CK_compare(	res= faculty<6>::value				, 720			)
//CK_compare(	typeid(faculty<6>::type)			, typeid(int_<720>)	)
}
