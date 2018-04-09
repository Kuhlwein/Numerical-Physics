#include "lsfit.h"
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

function<double(double)> eval(const vector<function<double(double)>> &funs, const vec &c) {
	return [funs,c](double x) {
		double sum=0;
		for(int i=0; i<funs.size(); i++) sum+=c[i]*funs[i](x);
		return sum;
	};
}

function<double(double)> eval_d(const vector<function<double(double)>> &funs, const mat &S) {
	return [funs,S](double x) {
		vec v(funs.size()); for(int i=0; i<funs.size(); i++) v(i)=funs[i](x);
		return sqrt(dot(v.t()*S,v));
	};
}

int main() {
	vector<function<double(double)>> funs
		= {[](double x){return log(x);}, [](double x){return 1;}, [](double x){return x;}};
	vec x = {0.1, 1.33, 2.55, 3.78, 5, 6.22, 7.45, 8.68, 9.9};
	vec y = {-15.3, 0.32, 2.45, 2.75, 2.27, 1.35, 0.157, -1.23, -2.75};
	vec dy = {1.04, 0.594, 0.983, 0.998, 1.11, 0.398, 0.535, 0.968, 0.478};
	vec c(3);
	mat S(3,3);

	lsfit(x,y,dy,funs,c,S);
	auto fit=eval(funs,c), fitd=eval_d(funs,S);
	
	for(int i=0; i<x.n_rows; i++) cout << x[i] << "\t" << y[i] << "\t" << dy[i] << "\n";
	cout << "\n\n";
	for(double i=x[0]; i<x[8]; i=i+0.1)
		cout << i << "\t" << fit(i) << "\t" << fit(i)+fitd(i) << "\t" << fit(i)-fitd(i) << "\n";

	cout << "\n\nCoefficients found by ls-fit with QR-decomposition:\n" << c
		<< "\nCovariance matrix found by ls-fit with QR-decomposition:\n" << S;

	lsfit_singular(x,y,dy,funs,c,S);
	cout << "\nCoefficients found by ls-fit with singular-value-decomposition:\n" << c
		<< "\nCovariance matrix found by ls-fit with singular-value-decomposition:\n" << S;
	return 0;
}
