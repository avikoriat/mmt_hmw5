#include <cmath>
#include "polynom.h"

//C'tor
polynom::polynom(int order, int* coefs) : n_(order){

	coefs_ = new int[order + 1];
	for (int i = 0; i <(order + 1); i++) {
		coefs_[i] = coefs[i];
	}
}
//D'tor
polynom::~polynom() {
	delete[] coefs_;
}
//copy C'tor
polynom::polynom(const polynom& rhs): n_(rhs.n_) {
	coefs_ = new int[rhs.n_ + 1];
	for (int i = 0; i < (rhs.n_ + 1); i++) {
		coefs_[i] = rhs.coefs_[i];
	}

}
//assignment operator
polynom& polynom::operator=(const polynom& rhs) {
	if (this != &rhs) {
		n_ = rhs.n_;
		if (coefs_) {
			delete[] coefs_;
		}
		coefs_ = new int[n_ + 1];
		for (int i = 0; i < (n_ + 1); i++) {
			coefs_[i] = rhs.coefs_[i];
		}
	}
	return *this;
}
/*************************************************************************
Function name	:operator<<
Description		:inserts the input x to the <input,output> map of the object
Paramerters		: x - a value to insert.
Return value	: polynom& - a reference to the lhs polynom to enable
	cascading of the << oprerator multiple times.
************************************************************************/
polynom& polynom::operator<<(const int& x) {
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
Function name	:operator+
Description		: calculates the addition of the lhs and the rhs polynoms
	and returns the value of the result.
Paramerters		: const polynom& lhs, const polynom& rhs - the left hand side
	and the right hand side of the operator.
Return value	: polynom - the result of the operation
************************************************************************/
polynom operator+(const polynom& lhs, const polynom& rhs) {
	int max_order = lhs.n_ > rhs.n_ ? lhs.n_ : rhs.n_;
	int min_order = lhs.n_ < rhs.n_ ? lhs.n_ : rhs.n_;
	int* max_coefs = lhs.n_ > rhs.n_ ? lhs.coefs_ : rhs.coefs_;
	int* coefsOfSum = new int[max_order + 1];
	for (int i = 0; i < (min_order + 1); i++) {
		coefsOfSum[i] = lhs.coefs_[i] + rhs.coefs_[i];
	}
	for (int i = min_order + 1; i < (max_order + 1); i++) {
		coefsOfSum[i] = max_coefs[i];
	}
	int newOrder = 0;
	for (int i = max_order; i >= 0; i--) {
		if (coefsOfSum[i] != 0) {
			newOrder = i;
			break;
		}
	}
	polynom polynomOfSum(newOrder, coefsOfSum);
	delete[] coefsOfSum;
	return polynomOfSum;
}
/*************************************************************************
Function name	:operator-
Description		: calculates the subtraction of the rhs polynom from the lhs
	 polynom and returns the value of the result.
Paramerters		: const polynom& lhs, const polynom& rhs - the left hand side
	and the right hand side of the operator.
Return value	:  polynom - the result of the operation
************************************************************************/
polynom operator-(const polynom& lhs, const polynom& rhs) {
	int max_order = lhs.n_ > rhs.n_ ? lhs.n_ : rhs.n_;
	int min_order = lhs.n_ < rhs.n_ ? lhs.n_ : rhs.n_;
	int* max_coefs = lhs.n_ > rhs.n_ ? lhs.coefs_ : rhs.coefs_;
	int* coefsOfsub = new int[max_order + 1];
	for (int i = 0; i < (min_order + 1); i++) {
		coefsOfsub[i] = lhs.coefs_[i] - rhs.coefs_[i];
	}
	for (int i = min_order + 1; i < (max_order + 1); i++) {
		coefsOfsub[i] = (lhs.n_ > rhs.n_)*max_coefs[i] - (lhs.n_ < rhs.n_)*max_coefs[i];
	}
	int newOrder = 0;
	for (int i = max_order; i >= 0; i--) {
		if (coefsOfsub[i] != 0) {
			newOrder = i;
			break;
		}
	}
	polynom polynomOfSub(newOrder, coefsOfsub);
	delete[] coefsOfsub;
	return polynomOfSub;
}
/*************************************************************************
Function name	:operator*
Description		: calculates the multiplication of the lhs and the rhs polynoms
	and returns the value of the result.
Paramerters		: const polynom& lhs, const polynom& rhs - the left hand side
	and the right hand side of the operator.
Return value	:  polynom - the result of the operation
************************************************************************/
polynom operator*(const polynom& lhs, const polynom& rhs) {
	
	int newCoefsSize = rhs.n_ + lhs.n_;
	int* coefsOfproduct = new int[newCoefsSize + 1];
	for (int i = 0; i < (newCoefsSize + 1); i++) {
		coefsOfproduct[i] = 0;
	}
	for (int i = 0; i < (rhs.n_ + 1); i++) {
		for (int j = 0; j < (lhs.n_ + 1); j++) {
			coefsOfproduct[i + j] += rhs.coefs_[i]* lhs.coefs_[j];
		}
	}
	int newOrder = 0;
	for (int i = newCoefsSize; i >= 0; i--) {
		if (coefsOfproduct[i] != 0) {
			newOrder = i;
			break;
		}
	}
	polynom polynomOfProduct(newOrder, coefsOfproduct);
	delete[] coefsOfproduct;
	return polynomOfProduct;
}
/*************************************************************************
Function name	:plot
Description		:plots the polynom formula, then its derivative formula,
	then its integral formula, then its graph.
Paramerters		: os - an ostream object.
Return value	: none
************************************************************************/
void polynom::plot(ostream& os) const {
	printcoefs(os);
	os << endl;
	os << "Derivative: ";
	polynom derivativePolynom = derivative();
	derivativePolynom.printcoefs(os);
	os << endl;
	os << "Integral: ";
	polynom integralPolynom = integral();
	integralPolynom.printcoefs(os);
	os << "+Constant"<<endl;
	func::plot(os);
}
/*************************************************************************
Function name	: derivative
Description		: returns the polynom of the object's derivative.
Paramerters		: none
Return value	: polynom
************************************************************************/
polynom polynom::derivative() const {
	int newOrder = (n_ > 0) ? (n_ - 1) : 0;
	int* coefsOfderivative = new int[newOrder + 1];
	if (n_ == 0) {
		coefsOfderivative[0] = 0;
	}
	else {
		for (int i = 0; i < (newOrder + 1); i++) {
			coefsOfderivative[i] = (i + 1) * coefs_[i + 1];
		}
	}
	polynom derivativePolynom(newOrder, coefsOfderivative);
	delete[] coefsOfderivative;
	return derivativePolynom;
}
/*************************************************************************
Function name	: integral
Description		: returns the polynom of the object's integral.
Paramerters		: none
Return value	: polynom
************************************************************************/
polynom polynom::integral() const {
	int newCoefSize = (n_==0 && coefs_[0]==0) ? 0 : n_ + 1;
	int* coefsOfintegral = new int[newCoefSize + 1];
	coefsOfintegral[0] = 0; // C = 0
	for (int i = 1; i < (newCoefSize + 1); i++) {
		coefsOfintegral[i] = coefs_[i - 1]/i;
	}
	int newOrder = 0;
	for (int i = newCoefSize; i >= 0; i--) {
		if (coefsOfintegral[i] != 0) {
			newOrder = i;
			break;
		}
	}
	polynom integralPolynom(newOrder, coefsOfintegral);
	delete[] coefsOfintegral;
	return integralPolynom;
}

/*************************************************************************
Function name	: getCoef
Description		: returns the polynom's i'th coefficient. if i is out of
	bound, throws an exception.
Paramerters		: i - the index of the desired coefficient
Return value	: int - the coefficient.
************************************************************************/
int polynom::getCoef(int i) const {
	if (0 <= i && i <= n_) {
		return coefs_[i];
	}
	else {
		throw("polynom::getCoef: out of range");
	}
}

/*************************************************************************
Function name	: evaluate
Description		: calculate's the polynom image on a speciefic input.
Paramerters		: x - the input
Return value	: int - the evaluation of the polynom on x
************************************************************************/
int polynom::evaluate(const int& x) const {
	int f_x = 0;
	for (int i = 0; i < (n_ + 1); i++) {
		f_x += coefs_[i] * (pow(x, i));
	}
	return f_x;
}

/*************************************************************************
Function name	: printcoefs
Description		: prints the polynom symbolic formula.
Paramerters		: os - an ostream object.
Return value	: none
************************************************************************/
void polynom::printcoefs(ostream& os)  const {

  int allZero = 1;
  for (auto i = n_ ; i>=0; i--) {
    if (coefs_[i]>0) {
		  allZero = 0;
		  if(i!=n_){
			os << "+";
		  }
		  if (coefs_[i]!=1 || i==0){
			os << coefs_[i];
		  }
		  if(i>0) {
			os << "x";
			if (i > 1) {
				os << "^" << i;
			}
		  }
    }
    else if(coefs_[i]<0) {
		  allZero = 0;
		  if (coefs_[i]!=-1 || i==0){
			os << coefs_[i];
		  }
		  else {
			  os << "-";
		  }
		  if(i>0) {
			os << "x";
			if (i > 1) {
				os << "^" << i;
			}
		  }
    }
    else if(i==0 && allZero == 1){ //coefs_[i]==0
        os << "0";
	continue;
    }
  }
}
