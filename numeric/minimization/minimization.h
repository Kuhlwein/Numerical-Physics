#include <armadillo>

void newton(std::function<double(arma::vec)> f, std::function<arma::vec(arma::vec)> df,
		std::function<arma::mat(arma::vec)> H, arma::vec &x, double dx, double eps);

void qnewton(std::function<double(arma::vec)> f, arma::vec &x, double dx, double eps,
		std::function<arma::vec(arma::vec)> df=NULL);
