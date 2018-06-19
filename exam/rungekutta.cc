#include "rungekutta.h"
#include <functional>
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

vec rk4(function<vec(double,vec)> dydt, double t, vec yt, double h) {
	vec k[4];
	k[0] = h*dydt(t,yt);
	k[1] = h*dydt(t+0.5*h,yt+0.5*k[0]);
	k[2] = h*dydt(t+0.5*h,yt+0.5*k[1]);
	k[3] = h*dydt(t+h,yt+k[2]);
	return yt+(k[0]+2*k[1]+2*k[2]+k[3])/6;
}

Driver::Driver(double acc, double eps, function<vec(function<vec(double,vec)>,double,vec,double)> rkx) {
	this->acc=acc; this->eps=eps; this->rkx=rkx;
}

double Driver::step(function<vec(double,vec)> dydt,double &t, vec &yt, double h) {
	vec y_full = rkx(dydt,t,yt,h);
	yt = rkx(dydt,t,yt,h/2); t+=0.5*h;
	yt = rkx(dydt,t,yt,h/2); t+=0.5*h;
	return norm((y_full-yt)/(pow(2,4)-1));
}

vec Driver::drive(function<vec(double,vec)> dydt,double t, vec yt, double h, double b) {
	double a=t, t1=t, err, tol; vec yt1=yt;
	while (b-t>1e-9) {
		if(t1+h>b) h=b-t1;
		err = step(dydt,t1,yt1,h);
		tol = (acc +norm(yt1)*eps)*sqrt(h/(b-a));
		if(tol>err) {t=t1; yt=yt1;} yt1=yt; t1=t;
		h = err>0 ? h*pow(tol/err,0.25)*0.95 : 2*h;
	}
	return yt;
}
