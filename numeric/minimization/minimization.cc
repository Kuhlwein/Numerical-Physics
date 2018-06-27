#include <armadillo>
#include <cmath>
#include "../lineq/qr_decomp.h"
using namespace std;
using namespace arma;

void newton(function<double(vec)> f, function<vec(vec)> df, function<mat(vec)> H, vec &x, double dx, double eps) {
	double fx=f(x); vec dfdx=df(x), Dx=-dfdx;
	do {
		mat B=H(x);
		qr_givens_decomp(B);
		qr_givens_solve(B,Dx);
		double lambda=1;
		while(f(x+lambda*Dx)>fx+0.1*lambda*dot(Dx,dfdx) && lambda>0.02) lambda/=2;
		x+=Dx; fx=f(x); dfdx=df(x); Dx=-dfdx;
	} while(norm(Dx)>dx && norm(dfdx)>eps);
}

function<vec(vec)> gradient(function<double(vec)> f, double dx) {
	return [f,dx](vec x) {
		int n = x.n_rows; mat J(n,n,fill::eye); vec G(n);
		for(int i=0; i<n; i++) G(i)=(f(x+J.col(i)*dx)-f(x))/dx;
		return G;
	};
}

void qnewton(function<double(vec)> f, vec &x, double dx, double eps, function<vec(vec)> df=NULL) {
	if(df==NULL) df=gradient(f,dx);
	double fx=f(x); vec dfdx=df(x), Dx=-dfdx;
	mat B = eye(x.n_rows,x.n_rows);
	do {
		Dx=-B*dfdx;
		vec s = Dx;
		double fxs=f(x+s);
		while (fxs>fx+0.1*dot(s,dfdx)) {
			s/=2; fxs=f(x+s);
			if(norm(s)<dx) {B=eye(x.n_rows,x.n_rows); break;}
		}
		vec dfdxs = df(x+s);
		vec y = dfdxs-dfdx;
		vec u = s-B*y;
		B+=u*u.t()/dot(u,y);
		x+=s; fx=fxs; dfdx=dfdxs; Dx=-dfdx;
	} while(norm(Dx)>dx && norm(dfdx)>eps);
}
