#include "root.h"
#include <iostream>
#include <armadillo>
#include <functional>
using namespace std;
using namespace arma;

int c;
function<vec(vec)> f = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return vec {10000*x*y-1, exp(-x)+exp(-y)-1-1./10000};
};
function<mat(vec)> fJ = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return mat {{10000*y, 10000*x},{-exp(-x), -exp(-y)}};
};

function<vec(vec)> rosenbrock = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return vec {400*(x*x*x-y*x)+2*x-2, 200*(y-x*x)};
};
function<mat(vec)> rosenbrockJ = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return mat {{400*(3*x*x-y)+2, -400*x},{-400*x, 200}};
};

function<vec(vec)> himmelblau = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return vec {2*(2*x*(x*x+y-11)+x+y*y-7), 2*(x*x+2*y*(x+y*y-7)+y-11)};
};
function<mat(vec)> himmelblauJ = [&c](vec v) {
	double x=v(0), y=v(1); c++;
	return mat {{12*x*x+4*y-42, 4*(x+y)},{4*(x+y), 4*(x+3*y*y-7)+2}};
};
vec a;

int main() {
	cout << "Newtons method with back-tracking linesearch and numerical jacobian:\n";
	a = {10, 1};c=0;
	newton(f,a,1e-3,1e-6);
	cout << "The system of equations A*x*y=1 and exp(-x)+exp(-y)=1+1/A is solved for A=1e4,\n"
		<< "using root-finding on f(x,y)=(A*x*y-1,exp(-x)+exp(-y)-1-1/A) in "
		<< c << " function calls:\nx="<<a(0)<<"\ny="<<a(1)<<"\n\n";

	a = {0, 0};c=0;
	newton(rosenbrock,a,1e-3,1e-6);
	cout << "The minimum for the rosenbrock function f(x,y) = (1-x)^2+100(y-x^2)^2 is found,\n"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\nx="<<a(0)<<"\ny="<<a(1)<<"\n\n";

	a = {0, 0};c=0;
	newton(himmelblau,a,1e-3,1e-6);
	cout << "The minimum for the himmelblau function f(x,y) = (x^2+y-11)^2+(x+y^2-7)^2 is found,\n"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\nx="<<a(0)<<"\ny="<<a(1)<<"\n\n";

	cout << "Newtons method with back-tracking linesearch and analytical jacobian:\n";
	a = {10, 1};c=0;
	newton_jacobian(f,fJ,a,1e-3,1e-6);
	cout << "The system of equations A*x*y=1 and exp(-x)+exp(-y)=1+1/A is solved for A=1e4,\n"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\nx="<<a(0)<<"\ny="<<a(1)<<"\n\n";
	
	a = {0, 0};c=0;
	newton_jacobian(rosenbrock,rosenbrockJ,a,1e-3,1e-6);
	cout << "The minimum for the rosenbrock function f(x,y) = (1-x)^2+100(y-x^2)^2 is found,\n"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\nx="<<a(0)<<"\ny="<<a(1)<<"\n\n";
	
	a = {0, 0};c=0;
	newton_jacobian(himmelblau,himmelblauJ,a,1e-3,1e-6);
	cout << "The minimum for the himmelblau function f(x,y) = (x^2+y-11)^2+(x+y^2-7)^2 is found,\n"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\nx="<<a(0)<<"\ny="<<a(1)<<"\n\n";
	return 0;
}
