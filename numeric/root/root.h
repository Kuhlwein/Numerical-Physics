#include <armadillo>
#include <functional>

void newton(std::function<arma::vec(arma::vec)> f, arma::vec &x, double dx, double eps);
void newton_jacobian(std::function<arma::vec(arma::vec)> f, std::function<arma::mat(arma::vec)> jacobian,
		arma::vec &x, double dx, double eps);
