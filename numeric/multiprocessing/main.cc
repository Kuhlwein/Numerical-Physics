#include "montecarlo.h"
#include <iostream>
#include <cmath>
using namespace std;

int c=0;
function<double(vector<double>)> f_divsq = [&c](vector<double> x) {c++;return 1/sqrt(x[0]);};
function<double(vector<double>)> f_pi = [&c](vector<double> x) {c++; return 4*sqrt(1-pow((1-x[0]),2));};
function<double(vector<double>)> fun = [&c](vector<double> x) {c++;return 1/(1-cos(x[0])*cos(x[1])*cos(x[2]))/pow(M_PI,3);};

int main() {
	double x,err;
	vector<double> a, b;
	
	c=0; a={0,0,0}; b={M_PI,M_PI,M_PI};
	x = plainmc(fun,a,b,1000000,err);
	cout << "integrating 1/[1-cos(x)cos(y)cos(z)]/pi^3 from x,y,z = 0 to pi:\nQ=" << x
		<< "\nCalls=" << c << "\nEstimated error=" << err << "\nActual error="
		<< abs(1.3932039296856768591842462603255-x) << "\n\n";

	c=0; a={0}; b={1};
	x = plainmc(f_divsq,a,b,1000000,err);
	cout << "integrating 1/sqrt(x) from 0 to 1:\nQ=" << x << "\nCalls=" << c
		<< "\nEstimated error=" << err << "\nActual error=" << abs(2-x) << "\n\n";
	
	c=0; a={0}; b={1};
	x = plainmc(f_pi,a,b,1000000,err);
	cout << "integrating 4*sqrt(1-(1-x)^2) from 0 to 1:\nQ=" << x << "\nCalls=" << c
		<< "\nEstimated error=" << err << "\nActual error=" << abs(M_PI-x) << "\n\n";
	
	c=0; a={0}; b={1};
	function<double(double,double)> f2d = [&c](double x, double y) {c++;return x*y;};
	function<double(double)> fc = [](double x) {return 0;};
	function<double(double)> fd = [](double x) {return x;};
	x = mc2d(f2d,fc,fd,a[0],b[0],1000000,err);
	cout << "integrating x*y from x=0 to 1 and y=0 to x:\nQ=" << x << "\nCalls=" << c
		<< "\nEstimated error=" << err << "\nActual error=" << abs(1./8-x) << "\n\n\n";

	for(int i=1e5; i<3e6; i+=1e5) {
		c=0; a={0}; b={1};
		x = plainmc(f_divsq,a,b,i,err);
		cout << i << "\t" << err << "\t" << abs(2-x) << "\n";
	}

	
	return 0;
}
