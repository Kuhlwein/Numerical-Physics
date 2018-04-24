#include <functional>
#include <vector>

double plainmc(std::function<double(std::vector<double>)> f, std::vector<double> a, 
		std::vector<double> b, int N, double &err);
