#include <stdio.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
#include <math.h>

struct data{int n; double *t,*y,*e;};

double fittingfunction(const gsl_vector* v, void* params, gsl_vector* f) {
	struct data p = *(struct data*) params;
	double A = gsl_vector_get(v,0), B = gsl_vector_get(v,1), T = gsl_vector_get(v,2), sum;
	for (int i=0; i<p.n; i++) sum+=pow((A*exp(-p.t[i]/T)+B-p.y[i])/p.e[i],2);
	return sum;
}

int main(int argc, char *argv[]) {
	double t[]= {0.47,1.41,2.36,3.30,4.24,5.18,6.13,7.07,8.01,8.95};
	double y[]= {5.49,4.08,3.54,2.61,2.09,1.91,1.55,1.47,1.45,1.25};
	double e[]= {0.26,0.12,0.27,0.10,0.15,0.11,0.13,0.07,0.15,0.09};
	int n = sizeof(t)/sizeof(t[0]);
	struct data p = {n, t, y, e};
	int dim = 3;
	
	gsl_multimin_fminimizer* state =
		gsl_multimin_fminimizer_alloc (gsl_multimin_fminimizer_nmsimplex2,dim);
	gsl_multimin_function F = {fittingfunction, dim, &p};
	gsl_vector* start = gsl_vector_calloc(dim);
	gsl_vector* step = gsl_vector_calloc(dim);
	gsl_vector_set_all(start,2);
	gsl_vector_set(start,0,5);
	gsl_vector_set_all(step,2);
	gsl_multimin_fminimizer_set(state, &F, start, step);

	int status = GSL_CONTINUE;
	for (int iter=0; status==GSL_CONTINUE && iter<500; iter++) {
		status = gsl_multimin_fminimizer_iterate(state);
		if(status) break;
		printf("A=%g,B=%g,T=%g\n",gsl_vector_get(state->x,0),gsl_vector_get(state->x,1),gsl_vector_get(state->x,2));

		status = gsl_multimin_test_size (state->size, 0.001);
		if (status == GSL_SUCCESS) printf("converged in %i iterations\n",iter);
	}
	double A=gsl_vector_get(state->x,0), B=gsl_vector_get(state->x,1), T=gsl_vector_get(state->x,2);
	for (int i=0; i<n; i++) printf("%g %g %g\n",t[i],y[i],A*exp(-t[i]/T)+B);
	return 0;
}
