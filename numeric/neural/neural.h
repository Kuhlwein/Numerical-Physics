#include <functional>
#include <vector>
#include <armadillo>

class Network {
	std::vector<int> layers;
	std::vector<std::function<arma::vec(arma::vec)>> f, df;
	std::vector<arma::mat> weights;
	std::vector<arma::vec> b;
	public:
		Network(std::vector<int> layers,std::vector<std::function<arma::vec(arma::vec)>> f,
				std::vector<std::function<arma::vec(arma::vec)>> df);
		arma::vec eval(arma::vec x);
		void train(std::vector<arma::vec> x, std::vector<arma::vec> y,
				double nu, double gamma,int batches);
};

std::function<arma::vec(arma::vec)> vecfun(std::function<double(double)> f);
