#include <iostream>

#if 0
template<typename T>
void foo_impl_unsigned(T arg) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

void foo(unsigned char arg) { foo_impl_unsigned(arg); }
void foo(unsigned short arg) { foo_impl_unsigned(arg); }
void foo(unsigned int arg) { foo_impl_unsigned(arg); }
void foo(unsigned long arg) { foo_impl_unsigned(arg); }
void foo(unsigned long long arg) { foo_impl_unsigned(arg); }


template<typename T>
void foo_impl_signed(T arg) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

void foo(signed char arg) { foo_impl_signed(arg); }
void foo(signed short arg) { foo_impl_signed(arg); }
void foo(signed int arg) { foo_impl_signed(arg); }
void foo(signed long arg) { foo_impl_signed(arg); }
void foo(signed long long arg) { foo_impl_signed(arg); }
#else

#include <type_traits>

#if __cplusplus >= 201402L
template<typename T>
std::enable_if_t<std::is_signed<T>::value && !std::is_floating_point<T>::value, void>
foo(T arg) { std::cout << "for signed: " <<  __PRETTY_FUNCTION__ << std::endl; }

template<typename T>
std::enable_if_t<std::is_unsigned<T>::value, void>
foo(T arg) { std::cout << "for unsigned: " << __PRETTY_FUNCTION__ << std::endl; }

template<typename T>
std::enable_if_t<std::is_floating_point<T>::value, void>
foo(T arg) { std::cout << "for floating_point: " << __PRETTY_FUNCTION__ << std::endl; }

#else // C++11

#if 1
template<typename T>
constexpr bool my_is_signed_integral() {
	return std::is_signed<T>::value && !std::is_floating_point<T>::value;
}

template<typename T>
typename std::enable_if<my_is_signed_integral<T>(), void>::type
foo(T arg) { std::cout << "for signed: " <<  __PRETTY_FUNCTION__ << std::endl; }

#else

template<typename T>
typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value, void>::type
foo(T arg) { std::cout << "for signed: " <<  __PRETTY_FUNCTION__ << std::endl; }

#endif

template<typename T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type
foo(T arg) { std::cout << "for unsigned: " << __PRETTY_FUNCTION__ << std::endl; }

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
foo(T arg) { std::cout << "for floating_point: " << __PRETTY_FUNCTION__ << std::endl; }
#endif


#endif

int main() {
	foo(1);
	foo(1u);
	foo(1L);
	foo(1.0);
	foo(1.0f);
	foo(1.0l);
}
