#include "compfunc.h"



compfunc::compfunc(const func& outer, const func& inner):inner_(inner),outer_(outer)
{}

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

void compfunc::plot(ostream& os) const {
	os << std::endl;
	func::plot(os);
}

int compfunc::evaluate(const int& x) const {
	return outer_.evaluate(inner_.evaluate(x));
}