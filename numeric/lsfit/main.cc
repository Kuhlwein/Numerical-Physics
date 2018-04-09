#include "lsfit.h"
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

function<double(double)> eval(const vector<function<double(double)>> funs, const vec c) {
	return [funs,c](double x) {
		double sum=0;
		for(int i=0; i<funs.size(); i++) sum+=c[i]*funs[i](x);
		return sum;
	};
}

int main() {
	vector<function<double(double)>> funs
		= {[](double x){return 1/x;}, [](double x){return 1;}, [](double x){return x;}};
	vec x = {0.100, 0.145, 0.211, 0.307, 0.447, 0.649, 0.944, 1.372, 1.995, 2.900};
	vec y = {12.644, 9.235, 7.377, 6.460, 5.555, 5.896, 5.673, 6.964, 8.896, 11.355};
	vec dy = {0.858, 0.359, 0.505, 0.403, 0.683, 0.605, 0.856, 0.351, 1.083, 1.002};
	vec c(3), dc;
	mat S(3,3);

	lsfit(x,y,dy,funs,c,S);
	dc = S.diag();
	auto fit=eval(funs,c), fitL=eval(funs,c-dc), fitH=eval(funs,c+dc);
	
	for(int i=0; i<x.n_rows; i++) cout << x[i] << "\t" << y[i] << "\t" << dy[i] << "\n";
	cout << "\n\n";
	for(double i=x[0]; i<x[9]; i=i+0.01)
		cout << i << "\t" << fit(i) << "\t" << fitL(i) << "\t" << fitH(i) << "\n";


	cout << "\n\n" << S << "\n" << c << "\n";

	lsfit_singular(x,y,dy,funs,c,S);
	cout << "\n\n" << S << "\n" << c << "\n";
	return 0;
}
