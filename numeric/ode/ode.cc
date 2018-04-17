#include "ode.h"
#include <armadillo>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;
using namespace arma;

function<void(double&,double&,vec&,vec&,vec&)> rkstep12(function<vec(double,vec)> &f) {
	return [&f](double &x0, double &h, vec &y0, vec &y1, vec &dy) {
		vec k0=f(x0,y0);
		vec k12=f(x0+h/2,y0+k0*h/2);
		y1=y0+k12*h;
		dy=(k0-k12)*h/2;
	};
}

void push_data(vector<vector<double>> &data,double x, vec y) {
	vector<double> entry = {x};
	for(double yi : y) entry.push_back(yi);
	data.push_back(entry);
}

vector<vector<double>> driver(double x,double b, vec y,
		function<void(double&,double&,vec&,vec&,vec&)> step, double dx, double acc, double eps) {
	vector<vector<double>> data; push_data(data,x,y);
	int n = y.n_rows;
	double a=x;
	vec dy(n), y1(n);
	while (x<b) {
		if(x+dx>b) dx=b-x;
		step(x,dx,y,y1,dy);
		double err = norm(dy);
		double tol = (acc + norm(y1)*eps)*sqrt(dx/(b-a));
		if(tol>err) {
			push_data(data,x+dx,y1);
			x+=dx;y=y1;
		}
		if(err>0) dx=dx*pow(tol/err,0.25)*0.95; else dx=2*dx;
	}
	return data;
}

double integral(function<double(double)> f, double a, double b) {
	function<vec(double,vec)> df = [f](double x, vec y) {return vec {f(x)};};
	auto d = driver(a,b,vec {0},rkstep12(df));
	return d.back().back();
}
