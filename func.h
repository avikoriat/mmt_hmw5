#ifndef FUNC_
#define FUNC_
#include <map>
#include <iostream>



using std::map;
using std::ostream;


class func {
 public:
	 func() :maxVal_(0), minVal_(0) {  };
	 virtual ~func() {};
	 friend ostream& operator<<(ostream& os, const func&);
	 virtual func& operator<<(const int& x) = 0;
	 virtual int evaluate(const int& x) const = 0;
 protected:  
	int maxVal_; //maximum of all inputs
	int minVal_; //minimum of all inputs
	map<int,int> fmap_; //holds inputs and corresponding outputs
	virtual void plot(ostream& os) const ; //plot fmap_
	bool isInitialized = false;
};


#endif

 