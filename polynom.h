#ifndef _POLY_F
#define _POLY_F

#include "func.h"

using namespace std;


class polynom : public func {
 public:
  void printcoefs(ostream&)  const ;
  polynom(int order,int* coefs);//c'tor
  virtual ~polynom();//d'tor
  polynom(const polynom& rhs);//copy c'tor
  polynom& operator=(const polynom& rhs);
  virtual polynom&  operator<<(const int& x);
  polynom derivative() const;
  polynom integral() const;
  friend polynom operator+(const polynom& lhs,const polynom& rhs);
  friend polynom operator-(const polynom& lhs, const polynom& rhs);
  friend polynom operator*(const polynom& lhs, const polynom& rhs);
  virtual void plot(ostream& os) const;
  int getOrder() const { return n_; }
  int getCoef(int i) const;
  int evaluate(const int& x) const;
protected:
  int n_; //order of the polynom
  int* coefs_; //coefficients 
};



#endif
 
