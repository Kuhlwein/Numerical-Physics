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

void qsplinePrep(const vector<double> &x, const vector<double> &y,
		vector<double> &c, vector<double> &b) {
	int n = x.size();
	vector<double> p(n-1), dx(n-1);
	for(int i=0; i<n-1;++i){dx[i]=x[i+1]-x[i]; p[i]=(y[i+1]-y[i])/dx[i];}
	c[0]=0;
	for(int i=0; i<n-2;++i) c[i+1]=(p[i+1]-p[i]-c[i]*dx[i])/dx[i+1];
	c[n-2]/=2;
	for(int i=n-3; i>=0;--i) c[i]=(p[i+1]-p[i]-c[i+1]*dx[i+1])/dx[i];
	for(int i=0; i<n-1;++i) b[i]=p[i]-c[i]*dx[i];
}

function<double(double)> qspline(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()-1);
	qsplinePrep(x,y,c,b);
	return [x,y,b,c](double z){
		int i = binarySearch(x,z);
		double h = z-x[i];
		return y[i]+h*(b[i]+h*c[i]);
	};
}
