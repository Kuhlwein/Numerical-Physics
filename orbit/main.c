#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>


int equation(double x, const double y[], double dydx[], void * params) {
	dydx[0] = y[0] * (1 - y[0]);
	return GSL_SUCCESS;
}


int main(int argc, char *argv[])
{
	//Exercise 1
	gsl_odeiv2_system diffequation;
	diffequation.function = equation;
	diffequation.jacobian = NULL;
	diffequation.dimension = 1;

	double hstart = 1e-3;
	double epsabs = 1e-6;
	double epsrel = 1e-6;
	double x_max = 3;
	double delta_x = 0.05;

	gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&diffequation, gsl_odeiv2_step_rk8pd, hstart, epsabs, epsrel);

	double t = 0;
	double y[1] = { 0.5 };

	for (double x = 0; x < x_max; x += delta_x) {
		int status = gsl_odeiv2_driver_apply(driver, &t, x, y);
		printf ("%g %g\n", x, y[0]);
		if (status != GSL_SUCCESS) fprintf (stderr, "fun: status=%i", status);
	}

	gsl_odeiv2_driver_free (driver);
	

	return 0;
}
