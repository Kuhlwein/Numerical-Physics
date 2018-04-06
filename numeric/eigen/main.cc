#include "jacobi.h"
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main() {
	mat Ao(5,5,fill::randu), A, V(5,5);
	Ao = symmatu(Ao); A=Ao;
	vec v(5);
	jacobi_cyclic(A,V,v);
	cout << "Let A be a symmetric matrix:\n" << Ao << "\n";
	cout << "Using jacobi_cyclic, V is found to be:\n" << V << "\n";
	cout << "The eigenvalues are found to:\n" << v << "\n";
	cout << "As expected, we find Vt*A*V=D:\n" << V.t()*Ao*V << "with eigenvalues on the diagonal.\n\n";

	A=Ao;
	jacobi_vbv(A,V,v,5);
	cout << "For jacobi_vbv for all five values, we find Vt*A*V=D:\n" << V.t()*Ao*V << "\n";

	A=Ao;
	jacobi_classic(A,V,v);
	cout << "And for jacobi_classic, we find Vt*A*V=D:\n" << V.t()*Ao*V << "\n";
	return 0;
}
