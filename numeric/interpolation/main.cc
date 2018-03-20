#include "spline.h"
#include <functional>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n = 20;
	vector<double> v(n), vv(n);

	for(int i=0; i<n; i++) {v[i]=i; vv[i]=sin(i);}

	function<double(double)> fun = cspline(v,vv);
	function<double(double)> fun2 = qspline(v,vv);
	function<double(double)> fun3 = lspline(v,vv);

	for(double i=0.; i<18; i=i+0.05) {
		cout << i << "\t" << fun(i) << "\t" << fun2(i) << "\t" << fun3(i) << "\n";
	}

	return 0;
}
