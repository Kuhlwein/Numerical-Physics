#include "ode.h"
#include <iostream>
#include <armadillo>
#include <functional>
using namespace std;
using namespace arma;
	
function<vec(double,vec)> f_cos = [](double x, vec y) {
	vec dydx(y.size());
	dydx(0)=y(1);
	dydx(1)=-y(0);
	return dydx;
};
function<vec(double,vec)> f_dampened = [](double x, vec y) {
	vec dydx(y.size());
	dydx(0)=y(1);
	dydx(1)=-y(0)-0.1*y(1);
	return dydx;
};

int main() {

	vector<vector<double>> data = driver(0,2*M_PI,vec {1, 0}, rkstep12(f_cos));
	cout << "By solving y''(x)=-y with y(0)=1 and y'(0)=0, we get cos(2*pi)=" 
		<< data.back().at(1) << "\n";
	
	vector<vector<double>> data2 = driver(0,2*M_PI,vec {1, 0}, rkstep12(f_dampened));
	cout << "By solving y''(x)=-y-y'(x)/10 with y(0)=1 and y'(0)=0, we get y(2*pi)=" 
		<< data2.back().at(1) << "\n";
	
	cout << "\n\n";
	for(vector<double> v : data) {
		for(double d : v) cout << d << "\t";
		cout << "\n";
	}
	cout << "\n\n";
	for(vector<double> v : data2) {
		for(double d : v) cout << d << "\t";
		cout << "\n";
	}

	return 0;
}
