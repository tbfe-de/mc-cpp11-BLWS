#ifndef CK_h
#define CK_h

#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>

#define CK_section(title)\
	CK::result_collector::instance.next_section(title);

#define CK_compare(statement, expected_value)\
	try {\
		CK::make_statement_executor(#statement, statement)\
			.compare(expected_value);\
	} catch(...) {\
		CK::unexpected_exception();\
	}

#define CK_throw_0(statement, exception_class)\
	try {\
		CK::statement_executor(#statement, statement);\
	} catch(...) {\
		CK::expected_exception<exception_class>(#exception_class);\
	}

#define CK_disable(reason)\
	CK::result_collector::instance.next_disabled(reason);

namespace CK {

	template <typename T>
	class statement_executor {
	public:
		statement_executor(
			const char *const textual_,
			const T &result_
		);
		void compare(
			const T &expected_value
		);

	private:
		const char *const textual;
		const T result;
	};

	class result_collector {
	public:
		void next_section(
			const char *const title
		);

		void next_disabled(
			const char* const reason
		);

		void add_passed(
			const char* const textual
		);

		template<typename T>
		inline
		void add_failed(
			const char *const textual,
			const T &result,
			const T &expectation
		);

		static result_collector instance;

	private:
		result_collector();
		~result_collector();

		const char *currentSection;
		int passCount;
		int failCount;
		std::ostringstream checksDetails;
		std::ostream &outputStream;
		bool showPassed;

		void section_results();
	};

	template<typename T>
	void result_collector::add_failed(
		const char *const textual,
		const T &expectation,
		const T& result
	) {
		checksDetails << "FAILED: " << textual << "\n";
		checksDetails << "  expected '" << expectation << "'\n";
		checksDetails << "  actually '" << result << "'\n";
		++failCount;
	}

	template<>
	inline
	void result_collector::add_failed<std::type_info>(
		const char *const textual,
		const std::type_info &expectation,
		const std::type_info& result
	) {
		checksDetails << "FAILED: " << textual << "\n";
		checksDetails << "  expected '" << expectation.name() << "'\n";
		checksDetails << "  actually '" << result.name() << "'\n";
		++failCount;
	}

	template<typename T>
	statement_executor<T>::statement_executor(
		const char *const textual_,
		const T &result_
	)
		: textual(textual_), result(result_)
	{}

	template<typename T>
	inline
	void statement_executor<T>::compare(
		const T &expected_value
	) {
		if (expected_value == result) {
			result_collector::instance.add_passed(textual);
		}
		else {
			result_collector::instance.add_failed(textual, expected_value, result);
		}
	}

	template<>
	class statement_executor<const std::type_info> {
	public:

		statement_executor(
			const char *const textual_,
			const std::type_info &result_
		);

		inline
		void compare(
			const std::type_info &expected_value
		);

	private:
		const char *textual;
		const std::type_info &result;
	};

	inline
	statement_executor<const std::type_info>::statement_executor(
		const char *const textual_,
		const std::type_info &result_
	)
		: textual(textual_), result(result_)
	{}

	inline
	void statement_executor<const std::type_info>::compare(
		const std::type_info &expected_value
	) {
		if (&expected_value == &result) {
			result_collector::instance.add_passed(textual);
		}
		else {
			result_collector::instance.add_failed(textual, expected_value, result);
		}
	}

	template<typename T>
	void expected_exception(
		const char* const textual_exception
	) {
		/*empty*/
	}
	
	void unexpected_exception();

	template<typename T>
	inline
	statement_executor<T> make_statement_executor(
		const char *const stext,
		const T& stmt
	) {
		return statement_executor<T>(stext, stmt);
	}

	inline
	statement_executor<const std::type_info> make_statement_executor(
		const char *const textual,
		const std::type_info& stmt
	) {
		return statement_executor<const std::type_info>(textual, stmt);
	}

}

#ifndef CK_SEPARATE_COMPILATION
#include "CK.cpp"
#endif

#endif
