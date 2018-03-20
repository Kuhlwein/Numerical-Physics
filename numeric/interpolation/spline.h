#include <functional>
#include <vector>
using namespace std;

function<double(double)> lspline(const vector<double> &x,const vector<double> &y);
function<double(double)> lsplineInteg(const vector<double> &x,const vector<double> &y);
function<double(double)> qspline(const vector<double> &x,const vector<double> &y);
