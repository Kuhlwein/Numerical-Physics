#include <armadillo>
#include <functional>

void newton(std::function<arma::vec(arma::vec)> f, arma::vec &x, double dx, double eps,
		std::function<arma::mat(arma::vec)> jacobian=NULL);

void newton_fancy(std::function<arma::vec(arma::vec)> f, arma::vec &x, double dx, double eps,
		std::function<arma::mat(arma::vec)> jacobian=NULL);
