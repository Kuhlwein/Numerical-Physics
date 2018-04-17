#include "minimization.h"
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

int main() {
	vec x = {2,2};
	newton(rosenbrock,drosenbrock,Hrosenbrock,x,1e-3,1e-6);
	cout << x << "\n" << c << "\n";

	x = {-1,-1}; c=0;
	newton(himmelblau,dhimmelblau,Hhimmelblau,x,1e-3,1e-6);
	cout << x << "\n" << c << "\n";
	
	
	x = {2,2}; c=0;
	qnewton(rosenbrock,drosenbrock,x,1e-3,1e-6);
	cout << x << "\n" << c << "\n";

	//x = {-1,-1}; c=0;
	//qnewton(himmelblau,dhimmelblau,x,1e-3,1e-6);
	//cout << x << "\n" << c << "\n";


	return 0;
}
