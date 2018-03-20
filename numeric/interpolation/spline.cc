#include <functional>
#include <vector>
#include "spline.h"
using namespace std;

int binarySearch(vector<double> vec, double x) {
	int i=0, j=vec.size()-1;
	while(i+1<j){int m=(i+j)/2; x>vec[m] ? i=m : j=m;}
	return i;
}

function<double(double)> lspline(const vector<double> &x, const vector<double> &y) {
	return [x,y](double z){
		int i = binarySearch(x,z);
		return y[i]+(y[i+1]-y[i])/(x[i+1]-x[i])*(z-x[i]);
	};
}

function<double(double)> lsplineInteg(const vector<double> &x, const vector<double> &y) {
	return [x,y](double z){
		function<double(double)> f = lspline(x,y);
		double sum = 0; int i;
		for (i = 0; x[i+1]<z; i++) sum+=(x[i+1]-x[i])*(y[i]+y[i+1])/2;
		return sum+=(z-x[i])*(y[i]+f(z))/2;
	};
}

void qsplinePrep(const vector<double> &x, const vector<double> &y,
		vector<double> &c, vector<double> &b) {
	int n = x.size();
	vector<double> p(n-1), dx(n-1);
	for(int i=0; i<n-1;++i){dx[i]=x[i+1]-x[i]; p[i]=(y[i+1]-y[i])/dx[i];}
	c[0]=0;
	for(int i=0; i<n-2;++i) c[i+1]=(p[i+1]-p[i]-c[i]*dx[i])/dx[i+1];
	c[n-2]/=2;
	for(int i=n-3; i>=0;--i) c[i]=(p[i+1]-p[i]-c[i+1]*dx[i+1])/dx[i];
	for(int i=0; i<n-1;++i) b[i]=p[i]-c[i]*dx[i];
}

function<double(double)> qspline(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()-1);
	qsplinePrep(x,y,c,b);
	return [x,y,b,c](double z){
		int i = binarySearch(x,z);
		double dx = z-x[i];
		return y[i]+dx*(b[i]+dx*c[i]);
	};
}

function<double(double)> qsplineDiff(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()-1);
	qsplinePrep(x,y,c,b);
	return [x,b,c](double z){
		int i = binarySearch(x,z);
		double dx = z-x[i];
		return (b[i]+dx*2*c[i]);
	};
}

function<double(double)> qsplineInteg(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()-1);
	qsplinePrep(x,y,c,b);
	return [x,y,b,c](double z){
		double sum = 0; int i;
		for (i = 0; x[i+1]<z; i++) {double dx=x[i+1]-x[i]; sum+=dx*(y[i]+dx*(b[i]/2+dx*c[i]/3));};
		double dx=z-x[i];
		return sum+=dx*(y[i]+dx*(b[i]/2+dx*c[i]/3));
	};
}

void csplinePrep(const vector<double> &x, const vector<double> &y,
		vector<double> &c, vector<double> &b, vector<double> &d) {
	int n = x.size();
	vector<double> p(n-1), dx(n-1), D(n), Q(n-1), B(n);

	for(int i=0; i<n-1;++i){dx[i]=x[i+1]-x[i]; p[i]=(y[i+1]-y[i])/dx[i];}
	
	D[0]=2; Q[0]=1; B[0]=3*p[0]; D[n-1]=2; B[n-1]=3*p[n-2];
	for(int i=0; i<n-2;++i) {
		D[i+1]=2*dx[i]/dx[i+1]+2;
		Q[i+1]=dx[i]/dx[i+1];
		B[i+1]=3*(p[i]+p[i+1]*dx[i]/dx[i+1]);
	}
	for(int i=0; i<n;++i) {
		D[i]-=Q[i-1]/D[i-1];
		B[i]-=B[i-1]/D[i-1];
	}

	b[n-1]=B[n-1]/D[n-1];
	for(int i=n-1; i>0; --i) b[i]=(B[i]-Q[i]*b[i+1])/D[i];
	for(int i=0; i<n-1; i++) {
		c[i] = (-2*b[i]-b[i+1]+3*p[i])/dx[i];
		d[i] = (b[i]+b[i+1]-2*p[i])/(dx[i]*dx[i]);
	}
}

function<double(double)> cspline(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()), d(x.size()-1);
	csplinePrep(x,y,c,b,d);
	return [x,y,b,c,d](double z){
		int i = binarySearch(x,z);
		double dx = z-x[i];
		return y[i]+dx*(b[i]+dx*(c[i]+dx*d[i]));
	};
}

function<double(double)> csplineDiff(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()), d(x.size()-1);
	csplinePrep(x,y,c,b,d);
	return [x,b,c,d](double z){
		int i = binarySearch(x,z);
		double dx = z-x[i];
		return (b[i]+dx*(2*c[i]+3*dx*d[i]));
	};
}

function<double(double)> csplineInteg(const vector<double> &x, const vector<double> &y) {
	vector<double> c(x.size()-1), b(x.size()), d(x.size()-1);
	csplinePrep(x,y,c,b,d);
	return [x,y,b,c,d](double z){
		double sum = 0; int i;
		for (i = 0; x[i+1]<z; i++) {double dx=x[i+1]-x[i]; sum+=dx*(y[i]+dx*(b[i]/2+dx*(c[i]/3+dx*d[i]/4)));};
		double dx=z-x[i];
		return sum+=dx*(y[i]+dx*(b[i]/2+dx*(c[i]/3+dx*d[i]/4)));
	};
}
