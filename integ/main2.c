#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

double normIntegrand(double x, void* params) {
	double a = *(double*)params;
	return exp(-a*x*x);
}

double hamiltonianIntegrand(double x, void* params) {
	double a = *(double*)params;
	return (-a*a*x*x/2+a/2+x*x/2)*exp(-a*x*x);
}

double E(double a) {
	gsl_function f;
	f.params = (void*)&a;

	int limit = 100;
	double result1, err, result2;
	gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(limit);

	f.function = normIntegrand;
	int status = gsl_integration_qagi(&f,1e-6,1e-6,limit,workspace,&result1,&err);
	if (status!=GSL_SUCCESS) result1=NAN;
	
	f.function = hamiltonianIntegrand;
	status = gsl_integration_qagi(&f,1e-6,1e-6,limit,workspace,&result2,&err);
	if (status!=GSL_SUCCESS) result2=NAN;

	return result2/result1;
}

int main(int argc, char *argv[])
{
	for (double i = 0.5; i <=2; i=i+0.01) {
		printf("%f\t%f\n",i,E(i));
	}
	return 0;
}
