#include "mathexception.h"

mathexception::mathexception(const char* exceptionString) {
	exceptionString_ = new char[strlen(exceptionString) + 1];
	strcpy(exceptionString_, exceptionString);
}

mathexception::~mathexception() {
	delete[] exceptionString_;
}
mathexception::mathexception(const mathexception& rhs) {
	exceptionString_ = new char[strlen(rhs.exceptionString_) + 1];
	strcpy(exceptionString_, rhs.exceptionString_);
}