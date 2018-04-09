#include <armadillo>
#include <vector>
#include <functional>
#include "../lineq/qr_decomp.h"
using namespace std;
using namespace arma;

void newton(function<vec(vec)> f, vec &x, double dx, double eps) {
	int n=x.n_rows;
	mat J(n,n);
	vec fx=f(x), Dx, df;
	do {
		for(int j=0; j<n; j++) {
			x(j)+=dx;
			df=f(x)-fx;
			for(int i=0; i<n; i++) J(i,j)=df(i)/dx;
			x(j)-=dx;
		}
		qr_givens_decomp(J);
		Dx=-fx;
		qr_givens_solve(J,Dx);
		
		double s=1;
		while(norm(f(x+Dx*s))>(1-s/2)*norm(fx) && s>0.02) s/=2;
		x=x+Dx*s; fx=f(x);
	} while (!(norm(Dx)<dx || norm(fx)<eps));
}
