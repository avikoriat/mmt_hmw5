#ifndef _RATFUNC
#define _RATFUNC
#include "func.h"
#include "polynom.h"
class ratfunc : public func {
public:
	ratfunc(const polynom& numerator, const polynom& denominator);//c'tor
	virtual ratfunc& operator<<(const int& x);
	virtual int evaluate(const int& x) const;
	friend ratfunc operator+(const ratfunc& lhs, const ratfunc& rhs);
	friend ratfunc operator-(const ratfunc& lhs, const ratfunc& rhs);
	friend ratfunc operator*(const ratfunc& lhs, const ratfunc& rhs);
	friend ratfunc operator/(const ratfunc& lhs, const ratfunc& rhs);
	virtual void plot(ostream& os) const;
	ratfunc derivative() const;
protected:
	polynom numerator_;
	polynom denominator_;
	
};

#endif
