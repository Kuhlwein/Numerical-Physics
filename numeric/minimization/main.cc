#include "minimization.h"
#include "downhillsimplex.h"
#include <iostream>
#include <armadillo>
#include <functional>
#include <cmath>
using namespace std;
using namespace arma;

int c=0;
function<double(vec)> rosenbrock = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return pow((1-x),2)+100*pow((y-x*x),2);
};
function<vec(vec)> drosenbrock = [](vec v) {
	double x=v(0), y=v(1);
	return vec {2*(x-1)-400*x*(y-x*x),200*(y-x*x)};
};
function<mat(vec)> Hrosenbrock = [](vec v) {
	double x=v(0), y=v(1);
	return mat {{2*x-400*(y-3*x*x),-400*x},{-400*x,200}};
};

function<double(vec)> himmelblau = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return pow((x*x+y-11),2)+pow((x+y*y-7),2);
};
function<vec(vec)> dhimmelblau = [](vec v) {
	double x=v(0), y=v(1);
	return vec {4*x*(x*x+y-11)+2*(x+y*y-7),2*(x*x+y-11)+4*y*(x+y*y-7)};
};
function<mat(vec)> Hhimmelblau = [](vec v) {
	double x=v(0), y=v(1);
	return mat {{4*(3*x*x+y-11)+2,4*(x+y)},{4*(x+y),2*y+4*(x+3*y*y-7)}};
};

double t[] = {0.23,1.29,2.35,3.41,4.47,5.53,6.59,7.65,8.71,9.77};
double y[] = {4.64,3.38,3.01,2.55,2.29,1.67,1.59,1.69,1.38,1.46};
double e[] = {0.42,0.37,0.34,0.31,0.29,0.27,0.26,0.25,0.24,0.24};
int N = sizeof(t)/sizeof(t[0]);

function<double(vec)> F = [&c,t,y,e,N](vec v) {
	double A=v(0), T=v(1), B=v(2), sum=0; c++;
	for(int i=0; i<N; i++) sum+=pow((A*exp(-t[i]/T)+B-y[i])/e[i],2);
	return sum;
};

int main() {
	cout << "Newtons method with backtracking line-search, with both user provided gradient and Hessian:\n";
	vec x = {2,2};
	newton(rosenbrock,drosenbrock,Hrosenbrock,x,1e-3,1e-6);
	cout << "\tThe minimum for the Rosenbrock function is found in " << c <<" function calls to:\n"
		<< "\tx: " << x(0) << "\n\ty: " << x(1) << "\n";

	x = {-4,-4}; c=0;
	newton(himmelblau,dhimmelblau,Hhimmelblau,x,1e-3,1e-6);
	cout << "\n\tThe minimum for the Himmelblau function is found in " << c 
		<<" function calls to:\n" << "\tx: " << x(0) << "\n\ty: " << x(1) << "\n";
	
	
	cout << "\nQuasi-Newtons method with Broyden's update, with user provided gradient:\n";
	x = {2,2}; c=0;
	qnewton(rosenbrock,x,1e-3,1e-6,drosenbrock);
	cout << "\tThe minimum for the Rosenbrock function is found in " << c <<" function calls to:\n"
		<< "\tx: " << x(0) << "\n\ty: " << x(1) << "\n";

	x = {-4,-4}; c=0;
	qnewton(himmelblau,x,1e-3,1e-6,dhimmelblau);
	cout << "\n\tThe minimum for the Himmelblau function is found in " << c 
		<<" function calls to:\n\tx: " << x(0) << "\n\ty: " << x(1) << "\n";
	cout << "For comparison with different root finding algorithm applied to the same problem, see ../root/out.txt\n In general it seems like minimization is better overall, although there are cases where root finding is slightly faster.\n";

	x = {1,1,1}; c=0;
	qnewton(F,x,1e-3,1e-6);
	cout << "\nFit using quasi-Newton method with Broyden's update without userprovided anything in " << c << " function calls:\n" << "\tFitresult:\n\tA: " << x(0) << "\n\tT: " << x(1) << "\n\tB: " << x(2) << "\n";

	cout << "\nDownhill simplex method:\n";
	mat simplex = {{5,10,5},{10,5,5}}; c=0;
	downhill_simplex(rosenbrock,simplex,1e-6);
	cout << "\tThe minimum for the Rosenbrock function is found in " << c << " function calls to:\n" 
		<< "\tx: " << simplex(0,0) << "\n\ty: " << simplex(1,0) << "\n";
	
	simplex = {{5,10,5},{10,5,5}};c=0;
	downhill_simplex(himmelblau,simplex,1e-6);
	cout << "\n\tThe minimum for the Himmelblau function is found in " << c << " function calls to:\n" << "\tx: " << simplex(0,0) << "\n\ty: " << simplex(1,0) << "\n";

	simplex = {{5,10,5,5},{10,5,5,2},{1,2,3,4}};c=0;
	downhill_simplex(F,simplex,1e-6);
	cout << "\n\tThe fitresult is found in " << c << " function calls to:\n" << "\tA: " << simplex(0,0) << "\n\tT: " << simplex(1,0) << "\n\tB: " << simplex(2,0) << "\n";



	cout << "\n";
	for(int i=0; i<N; i++) cout << t[i] << "\t" << y[i] << "\t" << e[i] << "\n";
	cout << "\n\n";
	for(double i=0; i<10; i+=.1) cout << i << "\t" << x(0)*exp(-i/x(1))+x(2) << "\n";

	return 0;
}
