#ifndef _COMPFUNC
#define _COMPFUNC
#include "func.h"

class compfunc : public func {
public:
	compfunc(const func& outer, const func& inner);
	virtual compfunc& operator<<(const int& x);
	void plot(ostream& os) const;
	virtual int evaluate(const int& x) const;
protected:
	const func& inner_;
	const func& outer_;
};
#endif
