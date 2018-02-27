#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

double integrand(double x, void* params) {
	return log(x)/sqrt(x);
}

int main(int argc, char *argv[])
{
	gsl_function f;
	f.function = integrand;
	int limit = 100;
	gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(limit);
	double result, err;
	int status = gsl_integration_qags(&f,0,1,1e-6,1e-6,limit,workspace,&result,&err);
	if (status!=GSL_SUCCESS) err=NAN;
	printf("int_0^1 ln(x)/sqrt(x) dx=%f\n", result);
	return 0;
}
