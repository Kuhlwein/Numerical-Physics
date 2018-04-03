#include <armadillo>

int jacobi_cyclic(arma::mat &A, arma::mat &V, arma::vec &v);
int jacobi_vbv(arma::mat &A, arma::mat &V, arma::vec &v, int n);
int jacobi_classic(arma::mat &A, arma::mat &V, arma::vec &v);
