#define CK_SEPARATE_COMPILATION
#include "CK.h"

namespace CK {

	result_collector::result_collector()
		: currentSection(0)
		, passCount(0)
		, failCount(0)
		, outputStream(std::cout)
		, showPassed(false)
	{
		checksDetails.setf(std::ios::boolalpha);
	}

	result_collector::~result_collector() {
		section_results();
	}

	void
	result_collector::section_results() {
		if (passCount + failCount > 0) {
			if (currentSection != 0) {
				outputStream << currentSection << ": ";
			}
			outputStream
				<< passCount << " of "
				<< passCount + failCount
				<< " passed\n"
				<< checksDetails.str();
			passCount = 0;
			failCount = 0;
			checksDetails.str(std::string());
		}
	}

	void
	result_collector::next_section(
		const char *const title
	) {
		section_results();
		currentSection = title;
	}

	void
	result_collector::add_passed(
		const char *const textual
	) {
		if (showPassed) {
			checksDetails << "PASSED: " << textual << "\n";
		}
		++passCount;
	}

	void
	result_collector::next_disabled(
		const char* const reason
	) {
		outputStream << reason << ": disabled (OK)\n";
	} 

	result_collector result_collector::instance;

	void unexpected_exception() {
	}
}
