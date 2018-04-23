#include "integration.h"
#include <functional>
#include <cmath>
using namespace std;

double adapt24(function<double(double)> f, double a, double b, double acc, double eps, double &err, double f2, double f3) {
	double f1=f(a+(b-a)/6), f4=f(a+5*(b-a)/6);
	double Q=(f1+f4)*(b-a)/3+(f2+f3)*(b-a)/6;
	double q=(f1+f2+f3+f4)*(b-a)/4;
	double tol=acc+abs(Q)*eps;
	err = abs(Q-q);
	if (err<tol) return Q;
	double e1, e2;
	double Q1=adapt24(f,a,(a+b)/2,acc/sqrt(2),eps,e1,f1,f2);
	double Q2=adapt24(f,(a+b)/2,b,acc/sqrt(2),eps,e2,f3,f4);
	err=sqrt(e1*e1+e2*e2);
	return Q1+Q2;
}

void fixinf(function<double(double)> &f, double &a, double &b) {
	double sign=1;
	if (isinf(a) && !isinf(b)) {double c=a; a=-b; b=-c;};
	if (b==-INFINITY) {sign=-1; a=-a; b=-b;}
	if (!isinf(a) && isinf(b)) {
		f=[f,a,sign](double x){return sign*f(a+x/(1-x))*1/pow((x-1),2);};
		a=0;b=1;
	} else if(isinf(a) && isinf(b)) {
		f=[f,sign](double x){return sign*f(x/(1-x*x))*(1+x*x)/pow((1-x*x),2);};
		a=-1;b=1;
	}
}

double integrate(function<double(double)> f, double a, double b, double &err,
		double eps, double acc) {
	fixinf(f,a,b);
	double f2=f(a+2*(b-a)/6), f3=f(a+4*(b-a)/6);
	return adapt24(f,a,b,acc,eps,err,f2,f3);
}

double integrateCC(function<double(double)> f, double a, double b, double &err,
		double eps, double acc) {
	fixinf(f,a,b);
	f=[f,a,b](double x){return f((a+b)/2+(a-b)/2*cos(x))*sin(x)*(b-a)/2;};
	return integrate(f,0,M_PI,err,eps,acc);
}
