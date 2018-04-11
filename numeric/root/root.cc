#include <armadillo>
#include <vector>
#include <functional>
#include "../lineq/qr_decomp.h"
using namespace std;
using namespace arma;

void newton_master(function<vec(vec)> f, function<mat(vec)> jacobi,
		function<double(vec,vec,vec)> lambda, vec&x, double dx, double eps) {
	vec fx=f(x), Dx, df;
	do {
		mat J=jacobi(x);
		qr_givens_decomp(J);
		Dx=-fx;
		qr_givens_solve(J,Dx);
		x=x+Dx*lambda(x,Dx,fx); fx=f(x);
	} while (norm(Dx)>dx && norm(fx)>eps);
}

function<mat(vec)> jacobi_num(function<vec(vec)> f, double dx) {
	return [f,dx](vec x) {
		int n = x.n_rows; mat J(n,n,fill::eye);
		for(int j=0; j<n; j++) J.col(j)=(f(x+J.col(j)*dx)-f(x))/dx;
		return J;
	};
}

function<double(vec,vec,vec)> linesearch_simple(function<vec(vec)> f) {
	return [f](const vec x, vec Dx, vec fx) {
		double s=1;
		while(norm(f(x+Dx*s))>(1-s/2)*norm(fx) && s>0.02) s/=2;
		return s;
	};
}

function<double(vec,vec,vec)> linesearch_fancy(function<vec(vec)> f) {
	return [f](const vec x, vec Dx, vec fx) {
		double s=1; vec fxs=f(x+Dx*s);
		while(norm(fxs)>(1-s/2)*norm(fx) && s>0.02) {
			double g0=dot(fx,fx)/2, gprime0=-dot(fx,fx);
			double gtrial=dot(fxs,fxs)/2, c = (gtrial-g0-gprime0*s)/(s*s);
			if(-gprime0/(2*c)<0.02) return s;
			s=-gprime0/(2*c); fxs=f(x+Dx*s);
		};
		return s;
	};
}

void newton(function<vec(vec)> f, vec &x, double dx, double eps,function<mat(vec)> jacobi=NULL) {
	if(jacobi==NULL) jacobi=jacobi_num(f,dx);
	newton_master(f,jacobi,linesearch_simple(f),x,dx,eps);
}

void newton_fancy(function<vec(vec)> f, vec &x, double dx, double eps,function<mat(vec)> jacobi=NULL) {
	if(jacobi==NULL) jacobi=jacobi_num(f,dx);
	newton_master(f,jacobi,linesearch_fancy(f),x,dx,eps);
}
