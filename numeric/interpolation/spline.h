#include <functional>
#include <vector>

std::function<double(double)> lspline(const std::vector<double> &x,const std::vector<double> &y);
std::function<double(double)> lsplineInteg(const std::vector<double> &x,const std::vector<double> &y);

std::function<double(double)> qspline(const std::vector<double> &x,const std::vector<double> &y);
std::function<double(double)> qsplineDiff(const std::vector<double> &x,const std::vector<double> &y);
std::function<double(double)> qsplineInteg(const std::vector<double> &x,const std::vector<double> &y);

std::function<double(double)> cspline(const std::vector<double> &x,const std::vector<double> &y);
std::function<double(double)> csplineDiff(const std::vector<double> &x,const std::vector<double> &y);
std::function<double(double)> csplineInteg(const std::vector<double> &x,const std::vector<double> &y);
