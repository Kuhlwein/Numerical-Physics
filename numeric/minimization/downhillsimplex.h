#include <armadillo>

void downhill_simplex(std::function<double(arma::vec)> f, arma::mat &simplex, double goal);
