#include <armadillo>

void qr_gs_decomp(arma::mat &A, arma::mat &R);
void qr_gs_solve(const arma::mat &Q, const arma::mat &R, arma::vec &b);
void qr_gs_inverse(const arma::mat &Q, const arma::mat &R, arma::mat &B);

void qr_givens_decomp(arma::mat &A);
void qr_givens_solve(const arma::mat &QR, arma::vec &b);
void qr_givens_inverse(const arma::mat &QR, arma::mat &B);
void qr_givens_getR(const arma::mat &QR, arma::mat &R);
void qr_givens_getQ(const arma::mat &QR, arma::mat &Q);
