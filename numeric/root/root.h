#include <armadillo>
#include <functional>

void newton(std::function<arma::vec(arma::vec)> f, arma::vec &x, double dx, double eps);
