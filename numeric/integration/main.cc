#include "integration.h"
#include <iostream>
#include <cmath>
using namespace std;

int c=0;
function<double(double)> f_sq = [&c](double x) {c++;return sqrt(x);};
function<double(double)> f_divsq = [&c](double x) {c++;return 1/sqrt(x);};
function<double(double)> f_logdivsq = [&c](double x) {c++;return log(x)/sqrt(x);};
function<double(double)> f_pi = [&c](double x) {c++; return 4*sqrt(1-pow((1-x),2));};
function<double(double)> f_divx2 = [&c](double x) {c++; return 1/x/x;};
function<double(double)> f_ex2 = [&c](double x) {c++; return exp(-x*x);};

void sqrtx(double x, double err) {
	cout << "\tintegrating sqrt(x) from 0 to 1:\n\tQ=" << x << "\n\tCalls=" << c
		<< "\n\tEstimated error=" << err << "\n\tActual error=\t" << abs(2./3-x) << "\n\n";
}
void divsqrtx(double x, double err) {
	cout << "\tintegrating 1/sqrt(x) from 0 to 1:\n\tQ=" << x << "\n\tCalls=" << c
		<< "\n\tEstimated error=" << err << "\n\tActual error=\t" << abs(2-x) << "\n\n";
}
void logdivsqrtx(double x, double err) {
	cout << "\tintegrating log(x)/sqrt(x) from 0 to 1:\n\tQ=" << x << "\n\tCalls=" << c
		<< "\n\tEstimated error=" << err << "\n\tActual error=\t" << abs(-4-x) << "\n\n";
}
void pix(double x, double err) {
	cout << "\tintegrating 4*sqrt(1-(1-x)^2) from 0 to 1:\n\tQ=" << x << "\n\tCalls=" << c
		<< "\n\tEstimated error=" << err << "\n\tActual error=\t" << abs(M_PI-x) << "\n\n";
}
void divx2(double x, double err) {
	cout << "\tintegrating 1/x^2 from 1 to inf:\n\tQ=" << x << "\n\tCalls=" << c
		<< "\n\tEstimated error=" << err << "\n\tActual error=\t" << abs(1-x) << "\n\n";
}
void ex2(double x, double err) {
	cout << "\tintegrating exp(-x^2) from -inf to inf:\n\tQ=" << x << "\n\tCalls=" << c
		<< "\n\tEstimated error=" << err << "\n\tActual error=\t" << abs(sqrt(M_PI)-x) << "\n\n";
}

int main() {
	double err,x;

	cout << "Adaptive24 using open quadratures\n";
	c=0; x=integrate(f_sq,0,1,err,1e-9,1e-9);
	sqrtx(x, err);
	c=0; x=integrate(f_divsq,0,1,err,1e-9,1e-9);
	divsqrtx(x, err);
	c=0; x=integrate(f_logdivsq,0,1,err,1e-9,1e-9);
	logdivsqrtx(x, err);
	c=0; x=integrate(f_pi,0,1,err,1e-9,1e-9);
	pix(x, err);
	c=0; x=integrate(f_divx2,1,INFINITY,err,1e-9,1e-9);
	divx2(x, err);
	c=0; x=integrate(f_ex2,-INFINITY,INFINITY,err,1e-9,1e-9);
	ex2(x, err);
	cout << "Adaptive24 using open quadratures and Clenshaw-Curtis\n";
	c=0; x=integrateCC(f_sq,0,1,err,1e-9,1e-9);
	sqrtx(x, err);
	c=0; x=integrateCC(f_divsq,0,1,err,1e-9,1e-9);
	divsqrtx(x, err);
	c=0; x=integrateCC(f_pi,0,1,err,1e-9,1e-9);
	pix(x, err);
	c=0; x=integrateCC(f_divx2,1,INFINITY,err,1e-9,1e-9);
	divx2(x, err);
	c=0; x=integrateCC(f_ex2,-INFINITY,INFINITY,err,1e-9,1e-9);
	ex2(x, err);


	return 0;
}
