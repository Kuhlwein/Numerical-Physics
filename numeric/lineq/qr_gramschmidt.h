#include <armadillo>
namespace qr_gs {
	void decomp(arma::mat &A, arma::mat &R);
	void solve(const arma::mat &Q, const arma::mat &R, arma::vec &b);
	void inverse(const arma::mat &Q, const arma::mat &R, arma::mat &B);
}
