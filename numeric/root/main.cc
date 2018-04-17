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

function<mat(vec)> squareroot2 = [&c](vec v) {
	double x=v(0); c++;
	return vec {x*x-2};
};
function<mat(vec)> squareroot2J = [&c](vec v) {
	double x=v(0); c++;
	return mat {2*x};
};
vec a;

void printeq(int c,vec a) {
	cout << "\tThe system of equations A*x*y=1 and exp(-x)+exp(-y)=1+1/A is solved for A=1e4,\n\t"
		<< "using root-finding on f(x,y)=(A*x*y-1,exp(-x)+exp(-y)-1-1/A) in "
		<< c << " function calls:\n\tx="<<a(0)<<"\n\ty="<<a(1)<<"\n\n";
}
void printrosen(int c,vec a) {
	cout << "\tThe minimum for the rosenbrock function f(x,y)=(1-x)^2+100(y-x^2)^2 is found,\n\t"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\n\tx="<<a(0)<<"\n\ty="<<a(1)<<"\n\n";
}
void printhimmel(int c,vec a) {
	cout << "\tThe minimum for the himmelblau function f(x,y)=(x^2+y-11)^2+(x+y^2-7)^2 is found,\n\t"
		<< "using root-finding on the gradient in "
		<< c << " function calls:\n\tx="<<a(0)<<"\n\ty="<<a(1)<<"\n\n";
}
void printsquareroot(int c,vec a) {
	cout << "\tThe square root of 2 is found, using root-finding on the function f(x)=x^2-2\n\tin "
		<< c << " function calls:\n\tx="<<a(0)<<"\n\n";
}

int main() {
	cout << "Newtons method with back-tracking linesearch and numerical jacobian:\n";
	a = {0, 1};c=0;
	newton(f,a,1e-3,1e-6);
	printeq(c,a);
	a = {2, 2};c=0;
	newton(rosenbrock,a,1e-3,1e-6);
	printrosen(c,a);
	a = {-4, -4};c=0;
	newton(himmelblau,a,1e-3,1e-6);
	printhimmel(c,a);
	a= {1};c=0;
	newton(squareroot2,a,1e-3,1e-6);
	printsquareroot(c,a);

	cout << "Newtons method with back-tracking linesearch and analytical jacobian:\n";
	a = {0, 1};c=0;
	newton(f,a,1e-3,1e-6,fJ);
	printeq(c,a);
	a = {2, 2};c=0;
	newton(rosenbrock,a,1e-3,1e-6,rosenbrockJ);
	printrosen(c,a);
	a = {-4, -4};c=0;
	newton(himmelblau,a,1e-3,1e-6,himmelblauJ);
	printhimmel(c,a);
	a= {1};c=0;
	newton(squareroot2,a,1e-3,1e-6,squareroot2J);
	printsquareroot(c,a);
	
	cout << "Newtons method with fancy linesearch and numerical jacobian:\n";
	a = {0, 1};c=0;
	newton_fancy(f,a,1e-3,1e-6);
	printeq(c,a);
	a = {2, 2};c=0;
	newton_fancy(rosenbrock,a,1e-3,1e-6);
	printrosen(c,a);
	a = {-4, -4};c=0;
	newton_fancy(himmelblau,a,1e-3,1e-6);
	printhimmel(c,a);
	a= {1};c=0;
	newton_fancy(squareroot2,a,1e-3,1e-6);
	printsquareroot(c,a);

	cout << "Newtons method with fancy linesearch and analytical jacobian:\n";
	a = {0, 1};c=0;
	newton_fancy(f,a,1e-3,1e-6,fJ);
	printeq(c,a);
	a = {2, 2};c=0;
	newton_fancy(rosenbrock,a,1e-3,1e-6,rosenbrockJ);
	printrosen(c,a);
	a = {-4, -4};c=0;
	newton_fancy(himmelblau,a,1e-3,1e-6,himmelblauJ);
	printhimmel(c,a);
	a= {1};c=0;
	newton_fancy(squareroot2,a,1e-3,1e-6,squareroot2J);
	printsquareroot(c,a);
	return 0;
}
