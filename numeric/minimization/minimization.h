#include <armadillo>

void newton(std::function<double(arma::vec)> f, std::function<arma::vec(arma::vec)> df,
		std::function<arma::mat(arma::vec)> H, arma::vec &x, double eps);
