#include "neural.h"
#include <functional>
#include <vector>
#include <armadillo>
using namespace std;
using namespace arma;

Network::Network(vector<int> layers,vector<function<vec(vec)>> f,vector<function<vec(vec)>> df) {
	this->layers = layers;
	this->f = f;
	this->df = df;
	weights.push_back(mat(1,1)); b.push_back(mat(1,1));
	for(int i=1; i<layers.size(); i++) {
		weights.push_back(mat(layers[i],layers[i-1],fill::randn));
		b.push_back(vec(layers[i],fill::randn));
	}
}

vec Network::eval(vec x) {
	for(int i=1; i<layers.size(); i++) x=f[i-1](weights[i]*x+b[i]);
	return x;
}

void Network::train(vector<vec> x, vector<vec> y, double nu, double gamma,int batches) {
	int n = layers.size();
	int m = x.size();
	vector<vec> b_update(n), b_update_old(n);
	vector<mat> w_update(n), w_update_old(n);
	for (int j=0; j<1000; j++) for(int l=0; l<batches; l++){
		for(int i=1; i<n; i++) {
			w_update_old[i]=(mat(layers[i],layers[i-1],fill::zeros));
			b_update_old[i]=(vec(layers[i],fill::zeros));
		}
		for(int k=l*(((double)m)/batches); k<(l+1)*((double)m)/batches; k++) {
			for(int i=1; i<n; i++) {
				w_update[i]=(mat(layers[i],layers[i-1],fill::zeros));
				b_update[i]=(vec(layers[i],fill::zeros));
			}
			vector<vec> z(n), a(n), delta(n);
			a[0]=x[k];
			for (int i=1; i<n; i++) {
				z[i]=(weights[i]*a[i-1]+b[i]);
				a[i]=(f[i-1](z[i]));
			}
			delta[n-1] = (a[n-1]-y[k]) % df[n-1-1](z[n-1]);
			for (int i=n-2; i>0; i--) {
				delta[i] = (weights[i+1].t()*delta[i+1]) % df[i-1](z[i]);
			}
			for(int i=1; i<n; i++) {
				w_update[i]+=delta[i]*a[i-1].t();
				b_update[i]+=delta[i];
			}
			for(int i=1; i<n; i++) {
				weights[i]-=(nu*w_update[i]+gamma*w_update_old[i])/(m);
				b[i]-=(nu*b_update[i]+gamma*b_update_old[i])/(m);
			}
			w_update_old = w_update; b_update_old = b_update;
		}
	}
}

function<vec(vec)> vecfun(const function<double(double)> f) {
	return [f](vec x) {for(int i=0; i<x.n_elem; i++) x[i]=f(x[i]); return x;};
}

