#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int motionEquation(double phi, const double u[], double uprime[], void * params) {
	double epsilon = *(double*) params;
	uprime[0] = u[1];
	uprime[1] = 1 - u[0] + epsilon * u[0] * u[0];
	return GSL_SUCCESS;
}

int main(int argc, char *argv[])
{
	double hstart = 1e-3, epsabs = 1e-6, epsrel = 1e-6;
	double x_max = 2*M_PI*10, delta_x = 0.05;
	
	gsl_odeiv2_system diffequation[3];
	gsl_odeiv2_driver *driver[3];
	double epsilon[3] = {0.0, 0.0, 0.01};

	for (int i = 0; i < 3; i++) {
		diffequation[i].function = motionEquation;
		diffequation[i].dimension = 2;
		diffequation[i].params = (void *) &(epsilon[i]);
		driver[i] = gsl_odeiv2_driver_alloc_y_new(&diffequation[i], gsl_odeiv2_step_rk8pd, hstart, epsabs, epsrel);
	}
	double t[3] = { 0, 0, 0 };
	double y[3][2] = { { 1, 0 }, { 1, -0.5 }, { 1, -0.5 } };

	for (double x = 0; x < x_max; x += delta_x) {
		for (int i = 0; i<3; i++) {
			int status = gsl_odeiv2_driver_apply(driver[i], &t[i], x, y[i]);
			if (status != GSL_SUCCESS) fprintf (stderr, "fun: status=%i", status);
		}
		printf ("%g %g %g %g\n", x, y[0][0], y[1][0], y[2][0]);
	}
	return 0;
}
