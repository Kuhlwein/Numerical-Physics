#include <armadillo>
#include <vector>
#include <functional>
#include "../lineq/qr_decomp.h"
#include "../eigen/jacobi.h"
using namespace std;
using namespace arma;

void lsfit(const vec &x, const vec &y, const vec &dy,
		const vector<function<double(double)>> &funs, vec &b, mat &S) {
	int n=x.n_rows, m=funs.size();
	mat A(n,m,fill::zeros), R(m,m), Q(n,m);
	b=y/dy;
	for(int i=0; i<n; i++) for(int k=0; k<m; k++) A(i,k)=funs[k](x[i])/dy[i];

	qr_givens_decomp(A);
	qr_givens_getR(A,R); qr_givens_getQ(A,Q);
	b = Q.t()*b;
	backsub(R,b);
	S = R.i()*R.i().t();
}

void singular_decomp(const mat &A, mat &U, mat &V, mat &Sigma) {
	mat AtA = A.t()*A; vec v(3);
	jacobi_classic(AtA,V,v);
	Sigma.diag() = pow(v,0.5);
	U = A*V*Sigma.i();
}

void lsfit_singular(const vec &x, const vec &y, const vec &dy,
		const vector<function<double(double)>> &funs, vec &b, mat &S) {
	int n=x.n_rows, m=funs.size();
	mat A(n,m,fill::zeros), U, V(3,3), sigma(3,3,fill::zeros);
	b=y/dy;
	for(int i=0; i<n; i++) for(int k=0; k<m; k++) A(i,k)=funs[k](x[i])/dy[i];
	
	singular_decomp(A,U,V,sigma);
	sigma.diag() = 1/sigma.diag();
	b = V*sigma*U.t()*b;
	S=V*pow(sigma,2)*V.t();
}
