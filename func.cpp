#include "func.h"
#include <vector>
#include <algorithm>
using namespace std;


ostream& operator<<(ostream& os, const func& function) {
	if (&function == nullptr) {
		throw nullptr;
	}
	function.plot(os);
	return os;
}
void func::plot(ostream& os) const{
	if (isInitialized) {
		vector<int> sortImage;
		//inserting map values:
		sortImage.clear();
		for (auto it : fmap_) {
			sortImage.push_back(it.second);
		}
		//sorting:
		class MapCompare {
		public:
			bool operator()(int a, int b) {
				return a < b;
			};
		};
		MapCompare compareObj;
		sort(sortImage.begin(), sortImage.end(), compareObj);

		//remove repeated:
		for (auto it_im = sortImage.begin();
			it_im != sortImage.end(); ++it_im) {
			if (it_im != sortImage.begin() && *it_im == *(it_im - 1)) {
				it_im = sortImage.erase(it_im) - 1;

			}
		}
		//reverse:
		reverse(sortImage.begin(), sortImage.end());


		for (auto it_im = sortImage.begin();
			it_im != sortImage.end(); ++it_im) {
			int x_anchor = minVal_;
			if (*it_im < -9)
				os << *it_im;
			else
				if ((*it_im < 0) || (*it_im > 9))
					os << " " << *it_im;
				else
					os << "  " << *it_im;

			for (auto it_dom : fmap_) {
				if (it_dom.second == *it_im) {
					int x = it_dom.first;
					int spaces = x - x_anchor;
					int i = 0;
					while (i < spaces) {
						os << "   ";
						i++;
					}
					os << "*  ";
					x_anchor = x + 1;
				}

			}

			os << endl;
			if ((it_im + 1) != sortImage.end()) { //print empty lines
				int lines = *it_im - *(it_im + 1) - 1;
				int i = 1;

				while (i < lines + 1) {
					if (*it_im - i < -9)
						os << *it_im - i;
					else
						if ((*it_im - i < 0) || (*it_im - i > 9))
							os << " " << *it_im - i;
						else
							os << "  " << *it_im - i;
					cout << endl;
					i++;

				}
			}

		}//for sortImage

		//print x axis
		cout << " ";
		for (auto i = minVal_; i < maxVal_ + 1; i++) {
			if (i < 0) os << " " << i;
			else os << "  " << i;
		}
		os << endl;
 }
}
