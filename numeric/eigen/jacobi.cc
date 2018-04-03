#include <armadillo>
#include <vector>
#include <cmath>
#include "jacobi.h"
using namespace std;
using namespace arma;

int rotate(mat &A, mat &V,int p, int q) {
	double phi=0.5*atan2(2*A(p,q),A(q,q)-A(p,p));
	double c = cos(phi), s = sin(phi);
	double app_new = c*c*A(p,p)-2*s*c*A(p,q)+s*s*A(q,q);
	double aqq_new = s*s*A(p,p)+2*s*c*A(p,q)+c*c*A(q,q);
	if(app_new==A(p,p) && aqq_new==A(q,q)) return 0;
	
	for(int i=0; i<A.n_cols; i++) {
		int ip=min(i,p), jp=max(i,p), iq=min(i,q), jq=max(i,q); 
		double aip=A(ip,jp), aiq=A(iq,jq);
		A(ip,jp)=c*aip-s*aiq; A(iq,jq)=c*aiq+s*aip;
	}
	A(p,p)=app_new; A(q,q)=aqq_new; A(p,q)=0.0;
	for(int i=0; i<A.n_cols; i++) {
		double vip = V(i,p), viq = V(i,q);
		V(i,p)=c*vip-s*viq; V(i,q)=c*viq+s*vip;
	}
	return 1;
}

int jacobi_cyclic(mat &A, mat &V, vec &v) {
	V.eye();
	int rotations = 0, rotations_old = 0;
	do {
		rotations_old = rotations;
		for(int p=0; p<A.n_cols; p++)
			for(int q=p+1; q<A.n_cols; q++) rotations += rotate(A,V,p,q);
	} while(rotations_old != rotations);
	v=A.diag();
	return rotations;
}

int jacobi_vbv(mat &A, mat &V, vec &v, int n) {
	V.eye();
	int rotations = 0, rotations_old = 0;
	for(int p=0; p<n; p++) do {
		rotations_old = rotations;
		for(int q=p+1; q<A.n_cols; q++) rotations += rotate(A,V,p,q);
	} while(rotations_old != rotations);
	v=A.diag();
	return rotations;
}

int rowmax(mat &A, int r) {
	int m = r+1;
	for(int c=r+1; c<A.n_cols; c++) if(abs(A(r,c))>abs(A(r,m))) m=c;
	return m;
}

int jacobi_classic(mat &A, mat &V, vec &v) {
	V.eye();
	vector<int> maxind(A.n_cols-1);
	for(int r=0; r<A.n_cols-1; r++) maxind[r] = rowmax(A,r);
	int rotations = 0, rotations_old = 0;
	do {
		rotations_old = rotations;
		int pmax = 0;
		for(int p=0; p<A.n_cols-1; p++) if(abs(A(p,maxind[p]))>abs(A(pmax,maxind[pmax]))) pmax=p;
		rotations += rotate(A,V,pmax,maxind[pmax]);
		for(int p=0; p<=pmax;  p++) if(maxind[p]==maxind[pmax]) maxind[p]=rowmax(A,p);
	} while(rotations_old != rotations);
	v=A.diag();
	return rotations;
}
