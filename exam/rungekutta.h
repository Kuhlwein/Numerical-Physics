#include <functional>
#include <vector>
#include <armadillo>

arma::vec rk4(std::function<arma::vec(double,arma::vec)> dydt,double t, arma::vec yt, double h);

class Driver {
	std::function<arma::vec(std::function<arma::vec(double,arma::vec)>,double,arma::vec,double)> rkx;
	double acc, eps;
	public:
		Driver(double acc, double eps, std::function<arma::vec(std::function<arma::vec(double,arma::vec)>,double,arma::vec,double)>);
		double step(std::function<arma::vec(double,arma::vec)> dydt,double &t, arma::vec &yt, double h);
		arma::vec drive(std::function<arma::vec(double,arma::vec)> dydt,double t, arma::vec yt, double h, double b);
};
