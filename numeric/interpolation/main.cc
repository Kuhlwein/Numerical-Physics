#include "spline.h"
#include <functional>
#include <vector>
#include <iostream>
#include <cmath>


using namespace std;

int main() {
	vector<double> v = {0, 2.3, 3.5, 4.6, 5.6, 7.6};
	vector<double> vv = {0, -2.3, 35.5, 43.6, 53.6, 6.6};
	function<double(double)> fun = lspline(v,vv);
	function<double(double)> fun2 = lsplineInteg(v,vv);
	cout << fun2(2.1) << "\n";
	cout << "test\n";
	return 0;
}
