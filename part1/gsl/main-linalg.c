#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
	//Exercise 2
	gsl_matrix* mat = gsl_matrix_calloc(3, 3);
	
	gsl_matrix_set(mat,0,0,6.13);
	gsl_matrix_set(mat,0,1,-2.90);
	gsl_matrix_set(mat,0,2,5.86);


	gsl_matrix_set(mat,1,0,8.08);
	gsl_matrix_set(mat,1,1,-6.31);
	gsl_matrix_set(mat,1,2,-3.86);
	
	gsl_matrix_set(mat,2,0,-4.36);
	gsl_matrix_set(mat,2,1,1.0);
	gsl_matrix_set(mat,2,2,0.19);

	gsl_vector* vec = gsl_vector_calloc(3);

	gsl_vector_set(vec,0,6.23);
	gsl_vector_set(vec,1,5.37);
	gsl_vector_set(vec,2,2.29);

	gsl_vector* vecRes = gsl_vector_calloc(3);
	//mat*vecRes = vec
	gsl_matrix* matCopy = gsl_matrix_calloc(3, 3);
	gsl_matrix_memcpy(matCopy,mat);
	int res = gsl_linalg_HH_solve(mat,vec,vecRes);
	
	printf("Solution is:\n");
	printf("%f\n", gsl_vector_get(vecRes,0));
	printf("%f\n", gsl_vector_get(vecRes,1));
	printf("%f\n", gsl_vector_get(vecRes,2));
	
	gsl_blas_dgemv(CblasNoTrans,1,matCopy,vecRes,0,vec);

	printf("Granting original rightside:\n");
	printf("%f\n", gsl_vector_get(vec,0));
	printf("%f\n", gsl_vector_get(vec,1));
	printf("%f\n", gsl_vector_get(vec,2));
	return 0;
}
