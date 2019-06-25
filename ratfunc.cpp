#include "ratfunc.h"
#include "mathexception.h"


ratfunc::ratfunc(const polynom& denominator, const polynom& numerator):
	 numerator_(numerator),denominator_(denominator) {
	if (denominator.getOrder() == 0 && denominator.getCoef(0) == 0) {
		throw mathexception("divide by zero");
	}
}

ratfunc& ratfunc::operator<<(const int& x) {
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

ratfunc operator+(const ratfunc& lhs, const ratfunc& rhs) {
	ratfunc sum((lhs.denominator_*rhs.denominator_),
		(lhs.numerator_*rhs.denominator_) + (lhs.denominator_*rhs.numerator_)
		);
	return sum;
}

ratfunc operator-(const ratfunc& lhs, const ratfunc& rhs) {
	ratfunc sub((lhs.denominator_*rhs.denominator_),
		(lhs.numerator_*rhs.denominator_) - (lhs.denominator_*rhs.numerator_)
		);
	return sub;
}

ratfunc operator*(const ratfunc& lhs, const ratfunc& rhs) {
	ratfunc prod((lhs.denominator_*rhs.denominator_),
		(lhs.numerator_*rhs.numerator_)
		);
	return prod;
}

ratfunc operator/(const ratfunc& lhs, const ratfunc& rhs) {
	if (rhs.numerator_.getOrder() == 0 && rhs.numerator_.getCoef(0) == 0) {
		throw mathexception("divide by zero");
	}
	ratfunc quot((lhs.denominator_*rhs.numerator_),
		(lhs.numerator_*rhs.denominator_)
		);
	return quot;
}

void ratfunc::plot(ostream& os) const {
	/*os << "printing ratfunc: " << endl;
	os << "numerator's coefs: " << endl;
	os << "numerator's order: " << numerator_.getOrder() << endl;
	os << "denominator's order: " << denominator_.getOrder() << endl;
	for (int i = 0; i < numerator_.getOrder() + 1; i++) {
		os << numerator_.getCoef(i)<<endl;
	}
	os << "denominator's coefs:" << endl;
	for (int i = 0; i < denominator_.getOrder() + 1; i++) {
		os << denominator_.getCoef(i) << endl;
	}
*/



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

ratfunc ratfunc::derivative() const {
	ratfunc derivative(denominator_ * denominator_,
		numerator_.derivative() * denominator_ -
		denominator_.derivative() * numerator_
		);
	return derivative;
}


int ratfunc::evaluate(const int& x) const {
	int denom_fx = denominator_.evaluate(x);
	if (denom_fx == 0) {
		throw mathexception("divide by zero");
	}
	int numer_fx = numerator_.evaluate(x);
	return numer_fx / denom_fx;
	
}

