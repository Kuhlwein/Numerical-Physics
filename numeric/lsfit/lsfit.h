#include <armadillo>
#include <functional>
#include <vector>

void lsfit(const arma::vec &x, const arma::vec &y, const arma::vec &dy,
		const std::vector<std::function<double(double)>> &funs, arma::vec &b, arma::mat &S);
void lsfit_singular(const arma::vec &x, const arma::vec &y, const arma::vec &dy,
		const std::vector<std::function<double(double)>> &funs, arma::vec &b, arma::mat &S);
