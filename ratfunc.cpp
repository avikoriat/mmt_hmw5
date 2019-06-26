#include "ratfunc.h"
#include "mathexception.h"

//C'tor
ratfunc::ratfunc(const polynom& denominator, const polynom& numerator):
	 numerator_(numerator),denominator_(denominator) {
	if (denominator.getOrder() == 0 && denominator.getCoef(0) == 0) {
		throw mathexception("divide by zero");
	}
}
/*************************************************************************
Function name	: operator<<
Description		: inserts the input x to the <input,output> map of the object
Paramerters		: x - a value to insert.
Return value	: ratfunc& - a reference to the lhs rational function
	to enable cascading the << oprerator multiple times.
************************************************************************/
ratfunc& ratfunc::operator<<(const int& x){
	int res;
	try {
		res = evaluate(x);
	}
	catch (exception& e) {
		throw;
		return *this;
	}
	fmap_[x] = res;
	if (!isInitialized) {
		minVal_ = maxVal_ = x;
		isInitialized = true;
	}
	else {
		if (x < minVal_) {
			minVal_ = x;
		}
		else if (x > maxVal_) {
			maxVal_ = x;
		}
	}
	
	return *this;
}
/*************************************************************************
Function name	: operator+
Description		: calculates the addition of the lhs and the rhs ratfuncs
	and returns the value of the result.
Paramerters		: const ratfunc& lhs, const ratfunc& rhs - the left hand side
	and the right hand side of the operator.
Return value	: ratfunc - the result of the operation
************************************************************************/
ratfunc operator+(const ratfunc& lhs, const ratfunc& rhs) {
	ratfunc sum((lhs.denominator_*rhs.denominator_),
		(lhs.numerator_*rhs.denominator_) + (lhs.denominator_*rhs.numerator_)
		);
	return sum;
}
/*************************************************************************
Function name	: operator-
Description		: calculates the subtraction of the rhs ratfunc from the lhs  
	ratfunc and returns the value of the result.
Paramerters		: const ratfunc& lhs, const ratfunc& rhs - the left hand side
	and the right hand side of the operator.
Return value	: ratfunc - the result of the operation
************************************************************************/
ratfunc operator-(const ratfunc& lhs, const ratfunc& rhs) {
	ratfunc sub((lhs.denominator_*rhs.denominator_),
		(lhs.numerator_*rhs.denominator_) - (lhs.denominator_*rhs.numerator_)
		);
	return sub;
}
/*************************************************************************
Function name	: operator*
Description		: calculates the multiplication of the lhs and the rhs ratfuncs
	and returns the value of the result.
Paramerters		: const ratfunc& lhs, const ratfunc& rhs - the left hand side
	and the right hand side of the operator.
Return value	: ratfunc - the result of the operation
************************************************************************/
ratfunc operator*(const ratfunc& lhs, const ratfunc& rhs) {
	ratfunc prod((lhs.denominator_*rhs.denominator_),
		(lhs.numerator_*rhs.numerator_)
		);
	return prod;
}
/*************************************************************************
Function name	: operator/
Description		: calculates the division of the lhs ratfunc by the rhs 
	ratfunc and returns the value of the result.
Paramerters		: const ratfunc& lhs, const ratfunc& rhs - the left hand side
	and the right hand side of the operator.
Return value	: ratfunc - the result of the operation
************************************************************************/
ratfunc operator/(const ratfunc& lhs, const ratfunc& rhs) {
	if (rhs.numerator_.getOrder() == 0 && rhs.numerator_.getCoef(0) == 0) {
		throw mathexception("divide by zero");
	}
	ratfunc quot((lhs.denominator_*rhs.numerator_),
		(lhs.numerator_*rhs.denominator_)
		);
	return quot;
}
/*************************************************************************
Function name	: plot
Description		: plots the rational function formula, then its derivative formula,
	then its graph.
Paramerters		: os - an ostream object.
Return value	: none
************************************************************************/
void ratfunc::plot(ostream& os) const {

	if (numerator_.getOrder() == 0 && numerator_.getCoef(0) == 0) {
		os << 0 << endl;
		os << "Derivative: 0" << endl;
	}
	else {
		os << '(';
		numerator_.printcoefs(os);
		os << ")/(";
		denominator_.printcoefs(os);
		os << ')' << endl;
		ratfunc derivative_ratfunc(derivative());
		os << "Derivative: ";
		if (derivative_ratfunc.numerator_.getOrder() == 0 && derivative_ratfunc.numerator_.getCoef(0) == 0) {
			 os<< 0 << endl;
		}
		else {
			os << '(';
			derivative_ratfunc.numerator_.printcoefs(os);
			os << ")/(";
			derivative_ratfunc.denominator_.printcoefs(os);
			os <<')'<< endl;
		}
	}
	func::plot(os);
}
/*************************************************************************
Function name	: derivative
Description		: returns the rational function of the object's derivative.
Paramerters		: none
Return value	: ratfunc - a rational function
************************************************************************/
ratfunc ratfunc::derivative() const {
	ratfunc derivative(denominator_ * denominator_,
		numerator_.derivative() * denominator_ -
		denominator_.derivative() * numerator_
		);
	return derivative;
}




/*************************************************************************
Function name	: evaluate
Description		: calculate's the rational function's image on a speciefic input.
Paramerters		: x - the input
Return value	: int - the evaluation of the ratfunc on x
************************************************************************/
int ratfunc::evaluate(const int& x) const {
	int denom_fx = denominator_.evaluate(x);
	if (denom_fx == 0) {
		throw mathexception("divide by zero");
	}
	int numer_fx = numerator_.evaluate(x);
	return numer_fx / denom_fx;
	
}

