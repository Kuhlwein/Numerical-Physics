#include "montecarlo.h"
#include <functional>
#include <vector>
#include <omp.h>
#include <random>
using namespace std;

double plainmc(function<double(vector<double>)> f, vector<double> a, vector<double> b, int N,
		double &err) {
	double V=1; for(int i=0; i<a.size(); i++) V*=b[i]-a[i];
	double sum=0, sum2=0;
	vector<double> x(a.size());
	
	#pragma omp parallel for reduction (+:sum,sum2)
	for(int i=0; i<N; i++) {
		mt19937::result_type seed = time(0);
		thread_local auto real_rand = std::bind(std::uniform_real_distribution<double>(0,1),mt19937(seed));
		for(int i=0; i<a.size(); i++) {x[i]=a[i]+real_rand()*(b[i]-a[i]);};
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
