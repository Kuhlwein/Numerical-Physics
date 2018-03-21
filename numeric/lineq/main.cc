#include "qr_decomp.h"
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

int main() {
	mat A(5,3,fill::randu), Q = A, R(3,3,fill::zeros);
	qr_gs_decomp(Q,R);
	cout << "Part A1:\n";
	cout << "Let A:\n" << A << "\n";
	cout << "using qr_gs_decomp, we get R:\n" << R << "\n";
	cout << "and Q:\n" << Q << "\nwith Q^(T)*Q:\n" << Q.t()*Q << "\n";
	cout << "and Q*R:\n" << Q*R << "\n";

	mat A2(3,3,fill::randu), Q2 = A2, R2(3,3,fill::zeros), B2 = A2;
	vec b2(3,fill::randu), x2=b2;
	qr_gs_decomp(Q2,R2);
	qr_gs_solve(Q2,R2,x2);
	cout << "Part A2:\n";
	cout << "Let A:\n" << A2 << "\n";
	cout << "and let b:\n" << b2 << "\n";
	cout << "Factorising A into Q*R as before,\nqr_gs_solve is used to find x for Q*R*x=b to:\n"
		<< x2 << "\n";
	cout << "with A*x:\n" << A2*x2 << "\n";
	
	qr_gs_inverse(Q2,R2,B2);
	cout << "Part B:\n";
	cout << "Using the same matrix A, qr_gs_inverse is used to find B:\n" << B2 << "\n";
	cout << "with A*B:\n" << A2*B2 << "\n";
	
	mat A3(3,3,fill::randu), Q3=A3, R3=A3, B3=A3, QR=A3;
	vec b3(3,fill::randu), x3=b3;
	qr_givens_decomp(QR);
	qr_givens_solve(QR,x3);
	qr_givens_inverse(QR,B3);
	qr_givens_getR(QR,R3);
	qr_givens_getQ(QR,Q3);
	cout << "Part C:\n";
	cout << "Let A:\n" << A3 << "\n";
	cout << "and let b:\n" << b3 << "\n";
	cout << "using qr_givens_decomp we get the rotation angles,\n" 
		<< "and by qr_givens_getR we get R:\n" << R3 << "\n";
	cout << "and by qr_givens_getQ we get Q:\n" << Q3 << "\nwith Q^(T)*Q:\n" << Q3.t()*Q3 << "\n";
	cout << "and Q*R:\n" << Q3*R3 << "\n";
	cout << "qr_givens_solve is used to find x for Q*R*x=b to:\n"
		<< x3 << "\n";
	cout << "with A*x:\n" << A3*x3 << "\n";
	cout << "qr_givens_inverse is used to find B:\n" << B3 << "\n";
	cout << "with A*B:\n" << A3*B3 << "\n";


	return 0;
}
