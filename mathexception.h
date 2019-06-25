#ifndef _MATHEXCEPTION
#define _MATHEXCEPTION
#include <exception>
#include <string.h>
using namespace std;

class mathexception : public exception {
public:
	mathexception(const char* exceptionString);//c'tor
	mathexception(const mathexception& rhs);
	~mathexception();
	virtual const char* what() const noexcept {
		return exceptionString_;
	}
protected:
	char* exceptionString_;
};

#endif
