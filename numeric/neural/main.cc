#include "neural.h"
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

function<vec(vec)> wav = vecfun([](double x) {return x*exp(-x*x);});
function<vec(vec)> dwav = vecfun([](double x) {return (1-2*x*x)*exp(-x*x);});
function<vec(vec)> f = vecfun([](double x) {return x;});
function<vec(vec)> df = vecfun([f](double x) {return 1;});

int main() {
	Network *n = new Network({1,2,1},{wav, f},{dwav, df});
	vector<vec> in(50), out(50);
	for (int i=0; i<50; i++) {
		vec v = vec(1,fill::randn);
		in[i] = v; out[i]=sin(5*v)*exp(-10*v*v);
	}
	n->train(in,out,2,0.01,4);
	cout << "\n\n";
	for (double i=0; i<1; i+=0.01) {
		vec e = n->eval({i});
		cout << i << "\t" << e.at(0) << "\t" << sin(5*i)*exp(-10*i*i)<< "\n";
	}
	
	cout << "\n\n";
	Network *n2 = new Network({2,6,1},{wav, f},{dwav, df});
	vector<vec> in2(50), out2(50);
	for (int i=0; i<50; i++) {
		vec v = vec(2,fill::randn);
		in[i] = v; out[i]={sin(5*v[0])+cos(1*v[1])};
	}
	n2->train(in,out,2,0,4);
	cout << "\n\n";
	for (double i=0; i<1; i+=0.01) for(double j=0; j<1; j+=0.01) {
		vec e = n2->eval({i, j});
		cout << i << "\t" << j << "\t" << e.at(0) << "\t" << sin(5*i)+cos(1*j)<< "\n";
	}
	return 0;
}
