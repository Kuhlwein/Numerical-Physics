#include <armadillo>
#include "../lineq/qr_decomp.h"
using namespace std;
using namespace arma;

void newton(std::function<double(arma::vec)> f, std::function<arma::vec(arma::vec)> df,
		std::function<arma::mat(arma::vec)> H, arma::vec &x, double eps) {
	double fx=f(x); vec dfdx=df(x), Dx=-dfdx;
	do {
		mat B=H(x);
		qr_givens_decomp(B);
		qr_givens_solve(B,Dx);
		double s=1;
		while(f(x+s*Dx)>fx+s*dot(Dx,dfdx)) s/=2;
		x+=Dx; fx=f(x); dfdx=df(x); Dx=-dfdx;
	} while(norm(df(x))>eps);
}
