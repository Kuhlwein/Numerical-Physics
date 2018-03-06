#include <stdio.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
#include <math.h>

double rosenbrock(const gsl_vector* v, void* params, gsl_vector* f) {
	double x = gsl_vector_get(v,0), y = gsl_vector_get(v,1);
	return pow((1-x),2)+100*pow((y-pow(x,2)),2);
}

int main(int argc, char *argv[]) {
	int dim = 2;
	gsl_multimin_fminimizer* state =
		gsl_multimin_fminimizer_alloc (gsl_multimin_fminimizer_nmsimplex2,dim);
	gsl_multimin_function F = {rosenbrock, dim, NULL};
	gsl_vector* start = gsl_vector_calloc(dim);
	gsl_vector* step = gsl_vector_calloc(dim);
	gsl_vector_set_all(step,0.05);
	gsl_multimin_fminimizer_set(state, &F, start, step);

	int status = GSL_CONTINUE;
	for (int iter=0; status==GSL_CONTINUE && iter<500; iter++) {
		status = gsl_multimin_fminimizer_iterate (state);
		if(status) break;
		printf("x=%g,y=%g\n",gsl_vector_get(state->x,0),gsl_vector_get(state->x,1));

		status = gsl_multimin_test_size (state->size, 0.001);
		if (status == GSL_SUCCESS) printf("converged in %i iterations\n",iter);
	}
	return 0;
}
