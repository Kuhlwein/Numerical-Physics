#include "qr_gramschmidt.h"
#include <iostream>
//#include <cmath>
#include <armadillo>
using namespace std;
using namespace arma;

int main() {
	mat Q = randu<mat>(5,5), R(5,5,fill::zeros), A = Q, B(5,5,fill::zeros);
  	vec b = randu<vec>(5);
  	//cout << Q << endl;
	qr_gs::decomp(Q,R);
	cout << Q*R << "\n";
	cout << R << "\n";

	cout << b << "\n";
	qr_gs::solve(Q,R,b);
	cout << b << "\n";
	cout << A*b << "\n";
	
	qr_gs::inverse(Q,R,B);

	cout << A << "\n";
	cout << A*B << "\n";

	

	return 0;
}
