#include "spline.h"
#include <functional>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n = 10;
	vector<double> v(n), vv(n);

	for(int i=0; i<n; i++) {v[i]=i; vv[i]=sin(i)*i; cout<<i<<"\t"<<sin(i)*i<<"\n";}
	cout << "\n\n";

	function<double(double)> funl = lspline(v,vv), funli = lsplineInteg(v,vv), funq = qspline(v,vv),
		funqd = qsplineDiff(v,vv), funqi = qsplineInteg(v,vv), func = cspline(v,vv),
		funcd = csplineDiff(v,vv), funci = csplineInteg(v,vv);

	for(double i=0.; i<9; i=i+0.05) {
		cout << i << "\t" << funl(i) << "\t" << funli(i) << "\t" 
			<< funq(i) << "\t" << funqd(i) << "\t" << funqi(i) << "\t" 
			<< func(i) << "\t" << funcd(i) << "\t" << funci(i) << "\t"
			<< sin(i)-i*cos(i) << "\t" << sin(i)+i*cos(i) << "\n";
	}

	return 0;
}
