#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int equation(double x, const double y[], double dydx[], void * params) {
	dydx[0] = 2/sqrt(M_PI)*exp(-x*x);
	return GSL_SUCCESS;
}

double myerf(double x) {
	gsl_odeiv2_system diffequation;
	diffequation.function = equation;
	diffequation.dimension = 1;

	double hstart = 1e-3, epsabs = 1e-6, epsrel = 1e-6;

	gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&diffequation, gsl_odeiv2_step_rk8pd, hstart, epsabs, epsrel);

	double t = 0,  y[1] = { 0.0 };
	int sign = (x >= 0) ? 1 : -1;
	int status = gsl_odeiv2_driver_apply(driver, &t, sign*x, y);
	gsl_odeiv2_driver_free (driver);
	return sign*y[0];
}

int main(int argc, char *argv[])
{
	for (double x = atoi(argv[1]); x <= atoi(argv[2]); x += atof(argv[3])) {
		printf("%g %g\n",x,myerf(x));
	}
	return 0;
}
