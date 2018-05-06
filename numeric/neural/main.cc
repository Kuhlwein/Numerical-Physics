#include "neural.h"
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

function<vec(vec)> wav = vecfun([](double x) {return x*exp(-x*x);});
function<vec(vec)> dwav = vecfun([](double x) {return (1-2*x*x)*exp(-x*x);});
function<vec(vec)> f = vecfun([](double x) {return x;});
function<vec(vec)> df = vecfun([](double x) {return 1;});
function<vec(vec)> softmax = [](vec x) {
		double xsum = 0;
		for(int i=0; i<x.n_elem; i++) xsum+=exp(x[i]);
		x = exp(x)/xsum;
		return x;
};
function<vec(vec)> dsoftmax = [softmax](vec x) {
	x = softmax(x)-(softmax(x)%softmax(x));
	return x;
};
function<vec(vec)> softplus = [](vec x) {
	x=log(1+exp(x));
	return x;
};
function<vec(vec)> dsoftplus = [](vec x) {
	x=1/(1+exp(-x));
	return x;
};


int main() {
	cout << "Number recognition at the bottom!\n";
	Network *n = new Network({1,2,1},{wav, f},{dwav, df});
	vector<vec> in(50), out(50);
	for (int i=0; i<50; i++) {
		vec v = vec(1,fill::randn);
		in[i] = v; out[i]=sin(5*v)*exp(-10*v*v);
	}
	n->train(in,out,2,0.01,4);
	for (double i=0; i<1; i+=0.01) {
		vec e = n->eval({i});
		cout << i << "\t" << e.at(0) << "\t" << sin(5*i)*exp(-10*i*i)<< "\n";
	}
	
	Network *n2 = new Network({2,6,1},{wav, f},{dwav, df});
	vector<vec> in2(50), out2(50);
	for (int i=0; i<50; i++) {
		vec v = vec(2,fill::randn);
		in[i] = v; out[i]={sin(5*v[0])+cos(1*v[1])};
	}
	n2->train(in,out,2,0.01,4);
	cout << "\n\n";
	for (double i=0; i<1; i+=0.01) for(double j=0; j<1; j+=0.01) {
		vec e = n2->eval({i, j});
		cout << i << "\t" << j << "\t" << e.at(0) << "\t" << sin(5*i)+cos(1*j)<< "\n";
	}
	cout << "\n\n";

	#include "letters.h"
	Network *n3 = new Network({35,5,5,10},{softplus, softplus, softmax},{dsoftplus, dsoftplus, dsoftmax});
	
	function<vec(vec,int,int)> shiftnum = [](vec x,int vert, int hors) {
		mat number = reshape(x,5,7);
		if (vert!=0) number = shift(number, -vert, 1);
		if (hors!=0) number = shift(number, hors, 0);
		number = reshape(number,35,1);
		return number;
	};

	mat answer = mat(10,10,fill::eye);
	vector<vec> input, output, num = {l1,l2,l3,l4,l5,l6,l7,l8,l9,l0};
	for (int i=0; i<100; i++) for(int count=0; count<10; count++) {
		vec randvec = vec(2,fill::randu)*4-2;
		//vec candidate = shiftnum(num[count],(int)randvec[0],(int)randvec[1]);
		input.push_back(num[count]);
		output.push_back(answer.col(count));
	}
	n3->train(input,output,2,0.01,5);

	function<vec(vec)> distortnum = [](vec x) {
		vec a = vec(1,fill::randu)*35;
		x[(int)a[0]] = 1-x[(int)a[0]];
		return x;
	};
	function<void(vec)> disp = [](vec x) {
		cout << reshape(x,5,7).t();
	};
	
	for(int i=0; i<9; i++) {
		vec test = distortnum(num[i]);
		vec prob = n3->eval(test);
		int maxval = prob.max()*100;
		int maxind = prob.index_max();
		cout << "The number " << i+1 << " with a  single pixel flipped,\n"
			<< "recognized with a 2-layer, 10 neuron network:\n";
		disp(test);
		cout << "Recognized as " << maxind+1 << " with " << maxval << "\% certainty!\n\n";
	}
	return 0;
}
