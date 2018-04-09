#include "root.h"
#include <iostream>
#include <armadillo>
#include <functional>
using namespace std;
using namespace arma;

int main() {
	function<vec(vec)> f = [](vec x) {
		x(0)=x(0)*x(0)-8;
		return x;
	};

	vec a = {10, 5};
	newton(f,a,1e-3,1e-7);

	cout << a << "\n";

	return 0;
}
