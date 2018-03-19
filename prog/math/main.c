#include <stdio.h>
#include <math.h>
#include <complex.h>

int main(int argc, char *argv[])
{
	int a = tgamma(5);
	printf("gamma(5)=%d\n",a);

	double b = j1(0.5);
	printf("j1(0.5)=%f\n",b);

	complex c = csqrt(-2);
	printf("sqrt(-2)=%g+%gi\n",creal(c),cimag(c));

	c = cexp(I);
	printf("exp(i)=%g+%gi\n",creal(c),cimag(c));
	
	c = cexp(I*M_PI);
	printf("exp(i*pi)=%g+%gi\n",creal(c),cimag(c));

	c = cpow(I,M_E);
	printf("i^e=%g+%gi\n",creal(c),cimag(c));
	
	float x = 0.1111111111111111111111111111;
	double y = 0.1111111111111111111111111111;
	long double z = 0.1111111111111111111111111111L;
	printf("float:       %.25g\n",x);
	printf("double:      %.25lg\n",y);
	printf("long double: %.25Lg\n",z);
	return 0;
}
