#include "montecarlo.h"
#include <functional>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

double plainmc(function<double(vector<double>)> f, vector<double> a, vector<double> b, int N,
		double &err) {
	double V=1; for(int i=0; i<a.size(); i++) V*=b[i]-a[i];
	double sum=0, sum2=0;
	vector<double> x(a.size());
	for(int i=0; i<N; i++) {
		for(int i=0; i<a.size(); i++) {x[i]=a[i]+(double)(rand())/RAND_MAX*(b[i]-a[i]);};
		double fx=f(x);
		sum+=fx; sum2+=fx*fx;
	}
	double avr=sum/N;
	err=sqrt((sum2/N-avr*avr)/N)*V;
	return avr*V;
}

double mc2d(std::function<double(double,double)> f, function<double(double)> c,
		function<double(double)> d, double a, double b, int N, double &err) {
	err=0; N = sqrt(N);
	function<double(vector<double>)> F = [f,c,d,&err,N](vector<double> x) {
		function<double(vector<double>)> f_inner = [f,x](vector<double> y) {
			return f(x[0],y[0]);
		};
		double newerr;
		double result =  plainmc(f_inner,{c(x[0])},{d(x[0])},N,newerr);
		err+=newerr;
		return result;
	};
	return plainmc(F,{a},{b},N,err);
}
