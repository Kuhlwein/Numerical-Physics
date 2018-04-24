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
