#include "spline.h"
#include <functional>
#include <vector>
#include <iostream>
#include <cmath>


using namespace std;

int main() {
	vector<double> v = {0, 2.3, 3.5, 4.6, 5.6, 7.6};
	vector<double> vv = {0, -2.3, 35.5, 43.6, 53.6, 6.6};
	function<double(double)> fun = qspline(v,vv);
	function<double(double)> fun2 = lspline(v,vv);

	for(double i=0.; i<7; i=i+0.05) {
		cout << i << "\t" << fun(i) << "\t" << fun2(i) << "\n";
	}

	return 0;
}
