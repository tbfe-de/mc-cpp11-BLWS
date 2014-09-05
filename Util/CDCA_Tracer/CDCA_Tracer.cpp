#include "CDCA_Tracer.h"

std::ostringstream CDCA_Tracer::messages;
unsigned long CDCA_Tracer::nextSerial;

CDCA_Tracer::CDCA_Tracer()
	: mySerial(++nextSerial)
{
	messages << "created <" << mySerial << ">\n";
}

CDCA_Tracer::CDCA_Tracer(const CDCA_Tracer &rhs)
	: mySerial(++nextSerial)
{
	messages << "created <" << mySerial
		 << "> from <" << rhs.mySerial << ">\n";
}

CDCA_Tracer::~CDCA_Tracer() {
	messages << "deleted <" << mySerial << ">\n";
}


void CDCA_Tracer::operator=(const CDCA_Tracer &rhs) {
	messages << "copied <" << mySerial
		 << "> from <" << rhs.mySerial << ">\n";
}

std::string CDCA_Tracer::getMessages() {
	const std::string tmp(messages.str());
	messages.str(std::string());
	return tmp;
}
