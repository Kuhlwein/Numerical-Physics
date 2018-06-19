#include "rungekutta.h"
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

function<vec(double,vec)> cosine = [](double t, vec y) {return vec{y(1), -y(0)};};
function<vec(double,vec)> gaussian = [](double t, vec y) {return vec{-t*y(0)};};
function<vec(double,vec)> logistic = [](double t, vec y) {return vec{y(0)*(1-y(0))};};

int main() {
	Driver driver = Driver(1e-6,1e-6,rk4);
	for (double i=0; i<5; i+=0.1) {
		cout << i << "\t"
			<< driver.drive(cosine,0,{1, 0},0.1,i).at(0) <<"\t"<< cos(i) << "\t"
			<< driver.drive(gaussian,0,{1},0.1,i).at(0) <<"\t"<< exp(-i*i/2) << "\t"
			<< driver.drive(logistic,0,{0.5},0.1,i).at(0) <<"\t"<< 1./(1+exp(-i)) << "\n";
	}
	return 0;
}
