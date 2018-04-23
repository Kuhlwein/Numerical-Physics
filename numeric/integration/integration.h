#include <functional>

double integrate(std::function<double(double)> f, double a, double b, double &err,
		double eps=1e-3, double acc=1e-3);

double integrateCC(std::function<double(double)> f, double a, double b, double &err,
		double eps=1e-3, double acc=1e-3);
