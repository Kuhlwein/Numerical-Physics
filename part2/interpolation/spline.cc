#include <functional>
#include <vector>
#include "spline.h"
using namespace std;

int binarySearch(vector<double> vec, double x) {
	int i=0, j=vec.size()-1;
	while(i+1<j){int m=(i+j)/2; x>vec[m] ? i=m : j=m;}
	return i;
}

function<double(double)> lspline(const vector<double> &x, const vector<double> &y) {
	return [x,y](double z){
		int i = binarySearch(x,z);
		return y[i]+(y[i+1]-y[i])/(x[i+1]-x[i])*(z-x[i]);
	};
}

function<double(double)> lsplineInteg(const vector<double> &x, const vector<double> &y) {
	return [x,y](double z){
		function<double(double)> f = lspline(x,y);
		double sum = 0; int i;
		for (i = 0; x[i+1]<z; i++) sum+=(x[i+1]-x[i])*(y[i]+y[i+1])/2;
		return sum+=(z-x[i])*(y[i]+f(z))/2;
	};
}
