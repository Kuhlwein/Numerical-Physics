#include <stdio.h>
#include <assert.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>

int ode_schrodinger(double r, const double y[], double dy[], void* params){
	double epsilon = *(double*)params;
	dy[0]=y[1];
	dy[1]= -2*(1/r+epsilon)*y[0];
	return GSL_SUCCESS;
}

double F(double epsilon, double r){
	double rmin = 1e-3;
	if(r<rmin) return r-r*r;

	gsl_odeiv2_system diffequation;
	diffequation.function = ode_schrodinger;
	diffequation.dimension = 2;
	diffequation.params = (void*) &epsilon;

	double hstart = 1e-3, epsabs = 1e-6, epsrel = 1e-6;
	gsl_odeiv2_driver* driver = gsl_odeiv2_driver_alloc_y_new (&diffequation, gsl_odeiv2_step_rk8pd, hstart, epsabs, epsrel);

	double t=rmin, y[2] = {t-t*t, 1-2*t};
	gsl_odeiv2_driver_apply (driver, &t, r, y);
	gsl_odeiv2_driver_free (driver);
	return y[0];
}

int M(const gsl_vector* v, void* params, gsl_vector* f) {
	double e=gsl_vector_get(v,0);
	double rmax=*(double*) params;
	gsl_vector_set(f,0,F(e,rmax));
	return GSL_SUCCESS;
}

int main(int argc, char *argv[]) {
	double rmax = 8.;
	int dim = 1, status=GSL_CONTINUE;

	gsl_multiroot_fsolver* solver =
		gsl_multiroot_fsolver_alloc (gsl_multiroot_fsolver_broyden, dim);
	gsl_multiroot_function func = {M, dim, (void*)&rmax};
	gsl_vector* x = gsl_vector_calloc(dim);
	gsl_vector_set(x,0,-1);
	gsl_multiroot_fsolver_set(solver, &func, x);

	for (int iter = 0; status == GSL_CONTINUE && iter<500; iter++) {
		status = gsl_multiroot_fsolver_iterate(solver);
		if(status) break;
		status = gsl_multiroot_test_residual(solver->f,1e-3);
	}
	double e = gsl_vector_get(solver->x,0);
	for(double r=0; r<=rmax; r+=rmax/128) printf("%g %g %g\n",r,F(e,r),r*exp(-r));
	return 0;
}
