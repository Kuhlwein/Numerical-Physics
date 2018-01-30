#include <stdio.h>
#include <math.h>
#include <complex.h>

int main(int argc, char *argv[])
{
	int a = tgamma(5);
	printf("gamma(5)=%d\n",a);

	double b = j1(0.5);
	printf("j1(0.5)=%g\n",b);

	complex c = csqrt(-2);
	printf("sqrt(-2)=%gi\n",cimag(c));

	complex d = cexp(I);
	printf("sqrt(-2)=%gi\n",cimag(d));
	
	complex f = csqrt(-2);
	printf("sqrt(-2)=%gi\n",cimag(c));
	return 0;
}
