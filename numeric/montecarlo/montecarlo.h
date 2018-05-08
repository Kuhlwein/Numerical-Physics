#include <functional>
#include <vector>

double plainmc(std::function<double(std::vector<double>)> f, std::vector<double> a, 
		std::vector<double> b, int N, double &err);

double mc2d(std::function<double(double,double)> f, std::function<double(double)> c,
		std::function<double(double)> d, double a, double b, int N, double &err);
