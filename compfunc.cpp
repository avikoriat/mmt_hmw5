#include "compfunc.h"


// C'tor
compfunc::compfunc(const func& outer, const func& inner):inner_(inner),outer_(outer)
{}
/*************************************************************************
Function name	: operator<<
Description		: inserts the input x to the <input,output> map of the object
Paramerters		: x - a value to insert.
Return value	: compfunc& - a reference to the lhs rational function
	to enable cascading the << operator multiple times.
************************************************************************/
compfunc& compfunc::operator<<(const int& x) {
	fmap_[x] = evaluate(x);
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
Function name	: plot
Description		: plots the composite function's graph.
Paramerters		: os - an ostream object.
Return value	: none
************************************************************************/
void compfunc::plot(ostream& os) const {
	os << std::endl;
	func::plot(os);
}
/*************************************************************************
Function name	: evaluate
Description		: calculate's the composite function's image on a speciefic 
	input.
Paramerters		: x - the input
Return value	: int - the evaluation of the composite function on x
************************************************************************/
int compfunc::evaluate(const int& x) const {
	return outer_.evaluate(inner_.evaluate(x));
}