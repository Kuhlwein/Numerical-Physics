#include <armadillo>
#include <functional>

std::function<void(double&,double&,arma::vec&,arma::vec&,arma::vec&)> rkstep12(
		std::function<arma::vec(double,arma::vec)> &f);

std::vector<std::vector<double>> driver(double x,double b, arma::vec y,
		std::function<void(double&,double& step,
		arma::vec&,arma::vec&,arma::vec&)>, double dx=.1, double acc=1e-3, double eps=1e-3);
