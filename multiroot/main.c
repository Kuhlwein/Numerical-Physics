#include <stdio.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_errno.h>

int rosenbrockDeriv(const gsl_vector * v, void * params, gsl_vector * f) {
	double x = gsl_vector_get(v,0), y = gsl_vector_get(v,1);
	gsl_vector_set(f,0,2*(x-1+200*x*x*x-200*x*y)); // d/dx
	gsl_vector_set(f,1,200*(y-x*x)); // d/dy
	return GSL_SUCCESS;
}

int main(int argc, char *argv[]) {
	int dim = 2;
	gsl_multiroot_fsolver* solver =
		gsl_multiroot_fsolver_alloc (gsl_multiroot_fsolver_broyden, dim);
	gsl_multiroot_function F = {rosenbrockDeriv, dim, NULL};
	gsl_vector* x = gsl_vector_calloc(dim);
	gsl_multiroot_fsolver_set(solver, &F, x);

	int status=GSL_CONTINUE;
	for (int iter = 0; status == GSL_CONTINUE && iter<500; iter++) {
		status = gsl_multiroot_fsolver_iterate(solver);
		if(status) break;
		printf("x=%g,y=%g\n",gsl_vector_get(solver->x,0),gsl_vector_get(solver->x,1));

		status = gsl_multiroot_test_residual(solver->f,1e-3);
		if(status==GSL_SUCCESS) printf("converged to x=%g,y=%g in %i iterations\n",
				gsl_vector_get(solver->x,0),gsl_vector_get(solver->x,1),iter);
	}
	return 0;
}
