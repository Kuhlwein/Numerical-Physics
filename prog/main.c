#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

struct data{int n; double x;};

double integrand(double t, void* params) {
	struct data p = *(struct data*)params;
	return 1/M_PI*cos(p.n*t-p.x*sin(t));
}

double J(int n, double x) {
	struct data p = {n,x};
	gsl_function f;
	f.params = (void*)&p;
	f.function = integrand;

	int limit = 100;
	double result, err, epsabs=1e-6, epsrel=1e-6;
	gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(limit);
	int status = gsl_integration_qag(&f,0,M_PI,epsabs,epsrel,limit,
			GSL_INTEG_GAUSS15,workspace,&result,&err);
	if (status!=GSL_SUCCESS) result=NAN;
	
	return result;
}

int main(int argc, char *argv[])
{
	for (double i = 1; i <=10; i=i+0.1) {
		printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\n",i,J(0,i),J(1,i),J(2,i),j0(i),j1(i),jn(2,i));
	}
	return 0;
}
