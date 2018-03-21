#include "qr_decomp.h"
#include <armadillo>
#include <cmath>
using namespace arma;

void backsub(const mat &U, vec &c) {
	for(int i=c.n_elem-1;i>=0;--i) {
		double s = c(i);
		for(int j=i+1; j<c.n_elem;j++) s-=U(i,j)*c(j);
		c(i) = s/U(i,i);
	}
}

void qr_gs_decomp(mat &A, mat&R) {
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

void qr_gs_solve(const mat &Q, const mat &R, vec &b) {
	b = Q.t()*b;
	backsub(R,b);
}

void qr_gs_inverse(const mat &Q, const mat &R, mat &B) {
	B.eye();
	for(int i=0;i<Q.n_rows;i++) {
		vec ei = B.unsafe_col(i);
		qr_gs_solve(Q,R,ei);
	}
}

void qr_givens_decomp(mat &A) {
	for(int q=0;q<A.n_cols;q++) {
		for(int p=q+1;p<A.n_rows;p++) {
			double theta=atan2(A(p,q),A(q,q));
			for(int k=q; k<A.n_cols; k++) {
				double xq=A(q,k), xp=A(p,k);
				A(q,k) = xq*cos(theta)+xp*sin(theta);
				A(p,k) = -xq*sin(theta)+xp*cos(theta);
			}
			A(p,q) = theta;
		}
	}
}

void qr_givens_QTvec(const mat &QR, vec &b) {
	for(int q=0; q<QR.n_cols;q++) {
		for(int p=q+1;p<QR.n_rows;p++) {
			double theta = QR(p,q);
			double bq=b(q), bp=b(p);
			b(q)=bq*cos(theta)+bp*sin(theta);
			b(p)=-bq*sin(theta)+bp*cos(theta);
		}
	}
}

void qr_givens_solve(const mat &QR, vec &b) {
	qr_givens_QTvec(QR,b);
	backsub(QR,b);
}

void qr_givens_inverse(const mat &QR, mat &B) {
	B.eye();
	for(int i=0;i<QR.n_rows;i++) {
		vec ei = B.unsafe_col(i);
		qr_givens_solve(QR,ei);
	}
}

void qr_givens_getR(const arma::mat &QR, arma::mat &R) {
	for(int c=0;c<R.n_cols;c++) for(int r=0;r<R.n_rows;r++)
		r<=c ? R(r,c)=QR(r,c) : R(r,c)=0;
}

void qr_givens_getQ(const arma::mat &QR, arma::mat &Q) {
	Q.eye();
	for(int i=0;i<QR.n_rows;i++) {
		vec ei = Q.unsafe_col(i);
		qr_givens_QTvec(QR,ei);
	}
	Q=Q.t();
}
