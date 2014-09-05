#ifndef CDCA_Tracer_h
#define CDCA_Tracer_h

#include <sstream>
#include <string>

class CDCA_Tracer {
	unsigned long mySerial;
	static unsigned long nextSerial;
	static std::ostringstream messages;
public:
	CDCA_Tracer();
	CDCA_Tracer(const CDCA_Tracer &);
	~CDCA_Tracer();
	void operator=(const CDCA_Tracer &);
	static std::string getMessages();
};

#endif
