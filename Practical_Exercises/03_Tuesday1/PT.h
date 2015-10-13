//! Some Versatile Macros for Small Examples.
//! @file

#include <iostream>

/*!
 * Helper to control the prefix printed by the other macros.
 *
 * The idea here is to avoid repeating an expression that should be
 * shown as the output from a small demo program as text and for
 * its evaluation.
 *
 * Using this macro is introduced to provide a central location to
 * change the destination of output or the prefix of each line.
 *
 * @note
 * For convenience this header includes the \<iostream\> header.
 *
 * @par To completely suppress the prefix:
 *
 * @code
 * #include "PT.h"
 * …
 * #undef L_
 * #define L_ std::cout <<
 * @endcode
 *
 * @par To change the destination:
 *
 * @code
 * #include "PT.h"
 * #include <ofstream>
 * …
 * #undef L_
 * #define ofs <<
 * …
 * int main() {
 *	std::ofstream ofs("name-the-destination");
 *	…
 * }
 * @endcode
*/
//!\hideinitializer
#define L_\
    std::cout << '[' << __FUNCTION__ << ":" << __LINE__ << ']'

/*!
 * Just print the value of an expression.
 *
 * Use this just to print the value of an expression together with the
 * expression itself textually prefixed.
 *
 * @param x the expression
 * @param ... further optional args
 *
 * @note
 * Optional argument is provided so that you can easily switch between
 * the three macros without having to edit out or in the expected value.
*/
//!\hideinitializer
#define P_(x, ...)\
    L_ << " " #x " == " << (x) << "\n"

/*!
 * Test the value of an expression.
 *
 * Use this if you want to test wether an expression has the excpected
 * value.
 *
 * @param x the xepression
 * @param u expected value
 *
 * @note
 * Output will \b only be generated if the value \b fails to meet the
 * expectation.
*/
//!\hideinitializer
#define T_(x_, u_)\
    do { const auto &x = (x_);\
         const auto &u = (u_);\
         if (x == u) break;\
         L_ << " " #x_ " == " << x << " != " << u << std::endl;\
    } while (0)

/*!
 * Print and test the value of an expression.
 *
 * Use this if you want print the value of an expression and also to test
 * whether it has an expected value.
 *
 * @param x the xepression
 * @param u expected value
 *
 * @note
 * Output will \b always be generated but the expectation is only contained
 * if it is \b not met.
*/
//!\hideinitializer
#define PT_(x_, u_)\
    do { const auto &x = (x_);\
         const auto &u = (u_);\
	 if (x == u) L_ << " " #x_ " == " << x << std::endl;\
	 else L_ << " "  #x_ " == " << x << " != " << u << std::endl;\
    } while (0)

/*!
 * Set default behaviour.
 *
 * @param x the xepression
 * @param u expected value
 *
 * Use this macro consequently if you want to change the behaviour of some
 * demo program with respect to the output generated in a single location.
 *
 * @todo add example
*/
#define X_(x, u) PT_(x, u)
