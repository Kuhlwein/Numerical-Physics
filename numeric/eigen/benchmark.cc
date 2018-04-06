#include "jacobi.h"
#include <iostream>
#include <ctime>
#include <armadillo>

using namespace std;
using namespace arma;

int main() {
	int N = 15, dN = 20, time, rotations;
	for(int n=dN; n<=N*dN; n+=dN) {
		mat A(n,n,fill::randn), Ac=A, V=A, Vc=V;
		vec v(n,fill::randn), vc=v;
		clock_t start, stop;
		cout << n << "\t";

		Ac=A, Vc=V; vc = v;
		start = clock();
		rotations = jacobi_cyclic(Ac,Vc,vc);
		stop = clock();
		time = 1000.*(stop-start)/CLOCKS_PER_SEC;
		cout << rotations << "\t" << time << "\t";
		
		Ac=A, Vc=V; vc = v;
		start = clock();
		rotations = jacobi_vbv(Ac,Vc,vc,1);
		stop = clock();
		time = 1000.*(stop-start)/CLOCKS_PER_SEC;
		cout << rotations << "\t" << time << "\t";
		
		Ac=A, Vc=V; vc = v;
		start = clock();
		rotations = jacobi_vbv(Ac,Vc,vc,5);
		stop = clock();
		time = 1000.*(stop-start)/CLOCKS_PER_SEC;
		cout << rotations << "\t" << time << "\n";
	}
	cout << "\n\n";
	N = 10; dN = 50;
	for(int n=dN; n<=N*dN; n+=dN) {
		mat A(n,n,fill::randn), Ac=A, V=A, Vc=V;
		vec v(n,fill::randn), vc=v;
		clock_t start, stop;
		cout << n << "\t";

		Ac=A, Vc=V; vc = v;
		start = clock();
		rotations = jacobi_cyclic(Ac,Vc,vc);
		stop = clock();
		time = 1000.*(stop-start)/CLOCKS_PER_SEC;
		cout << rotations << "\t" << time << "\t";
		
		Ac=A, Vc=V; vc = v;
		start = clock();
		rotations = jacobi_classic(Ac,Vc,vc);
		stop = clock();
		time = 1000.*(stop-start)/CLOCKS_PER_SEC;
		cout << rotations << "\t" << time << "\n";
	}
	return 0;
}
