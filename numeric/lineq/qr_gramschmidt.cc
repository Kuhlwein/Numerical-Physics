#include "qr_gramschmidt.h"
#include <armadillo>
using namespace arma;

void qr_gs::decomp(mat &A, mat&R) {
	int m = A.n_cols;
	for(int i=0; i<m;i++) {
		R(i,i) = norm(A.col(i));
		A.col(i) = A.col(i)/R(i,i);
		for(int j=i+1;j<m;j++) {
			R(i,j)=cdot(A.col(i),A.col(j));
			A.col(j)-=R(i,j)*A.col(i);
		}
	}
}

void qr_gs::solve(const mat &Q, const mat &R, vec &b) {
	b = Q.t()*b;
	for(int i=b.n_elem-1;i>=0;--i) {
		double s = b(i);
		for(int j=i+1; j<b.n_elem;j++) s-=R(i,j)*b(j);
		b(i) = s/R(i,i);
	}
}

void qr_gs::inverse(const mat &Q, const mat &R, mat &B) {
	for(int i=0;i<Q.n_rows;i++) {
		vec b = vec(Q.n_cols,fill::zeros);
		b(i)=1;
		qr_gs::solve(Q,R,b);
		B.col(i)=b;
	}
}
