#include <iostream>
#include <complex>
#include <cmath>

int main(int argc, char *argv[])
{
	int a = tgamma(5);
	printf("gamma(5)=%d\n",a);

	double b = j1(0.5);
	printf("j1(0.5)=%f\n",b);

	std::complex<double> i(0,1);
	std::complex<double> c = -2;
	c = sqrt(c);
	std::cout << "sqrt(-2)=" << c << "\n";

	c = exp(i);
	std::cout << "exp(i)=" << c << "\n";
	
	c = exp(i*M_PI);
	std::cout << "exp(i*pi)=" << c << "\n";

	c = pow(i,M_E);
	std::cout << "i^e=" << c << "\n";

	float x = 0.1111111111111111111111111111;
	double y = 0.1111111111111111111111111111;
	long double z = 0.1111111111111111111111111111L;
	printf("float:       %.25g\n",x);
	printf("double:      %.25lg\n",y);
	printf("long double: %.25Lg\n",z);
	return 0;
}
