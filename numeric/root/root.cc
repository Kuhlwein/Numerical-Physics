#include <armadillo>
#include <vector>
#include <functional>
#include "../lineq/qr_decomp.h"
using namespace std;
using namespace arma;

void newton(function<vec(vec)> f, vec &x, double dx, double eps) {
	int n=x.n_rows;
	mat J(n,n), I(n,n,fill::eye);
	vec fx=f(x), Dx, df;
	do {
		for(int j=0; j<n; j++) J.col(j)=(f(x+I.col(j)*dx)-f(x))/dx;
		qr_givens_decomp(J);
		Dx=-fx;
		qr_givens_solve(J,Dx);
		
		double s=1;
		while(norm(f(x+Dx*s))>(1-s/2)*norm(fx) && s>0.02) s/=2;
		x=x+Dx*s; fx=f(x);
	} while (!(norm(Dx)<dx || norm(fx)<eps));
}
