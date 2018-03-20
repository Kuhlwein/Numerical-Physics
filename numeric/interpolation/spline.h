#include <functional>
#include <vector>
using namespace std;

function<double(double)> lspline(const vector<double> &x,const vector<double> &y);
function<double(double)> lsplineInteg(const vector<double> &x,const vector<double> &y);

function<double(double)> qspline(const vector<double> &x,const vector<double> &y);
function<double(double)> qsplineDiff(const vector<double> &x,const vector<double> &y);
function<double(double)> qsplineInteg(const vector<double> &x,const vector<double> &y);

function<double(double)> cspline(const vector<double> &x,const vector<double> &y);
function<double(double)> csplineDiff(const vector<double> &x,const vector<double> &y);
function<double(double)> csplineInteg(const vector<double> &x,const vector<double> &y);
