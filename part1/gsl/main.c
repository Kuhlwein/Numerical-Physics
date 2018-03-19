#include <stdio.h>
#include <gsl/gsl_sf_airy.h>
#include <math.h>

int main(int argc, char *argv[])
{
	//Exercise 1
	for (double i = -2; i < 2; i=i+0.01) {
		double Ai = gsl_sf_airy_Ai(i, GSL_PREC_DOUBLE);
		double Bi = gsl_sf_airy_Bi(i, GSL_PREC_DOUBLE);
		printf("%lg \t %lg \t %lg\n",i,Ai,Bi);
	}
	return 0;
}
