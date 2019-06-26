#include "mathexception.h"
//C'tor
mathexception::mathexception(const char* exceptionString) {
	exceptionString_ = new char[strlen(exceptionString) + 1];
	strcpy(exceptionString_, exceptionString);
}
//D'tor
mathexception::~mathexception() {
	delete[] exceptionString_;
}
//Copy C'tor
mathexception::mathexception(const mathexception& rhs) {
	exceptionString_ = new char[strlen(rhs.exceptionString_) + 1];
	strcpy(exceptionString_, rhs.exceptionString_);
}