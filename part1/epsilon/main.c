#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "equal.h"

int main(int argc, char *argv[])
{
	//1 - i
	int i=1; while(i+1>i) {++i;}
	printf("%i (while method)\n",i);
	i=1; do{++i;}while(i+1>i);
	printf("%i (dowhile method)\n",i);
	for (i = 0; i < i+1; ++i) {}
	printf("%i (forloop method)\n",i);
	printf("%i (INT_MAX)\n\n", INT_MAX);

	//1 - ii
	i=1; while(i>i-1) {--i;}
	printf("%i (while method)\n",i);
	i=1; do{--i;}while(i>i-1);
	printf("%i (dowhile method)\n",i);
	for (i = 0; i-1 < i; --i) {}
	printf("%i (forloop method)\n",i);
	printf("%i (INT_MIN)\n\n", INT_MIN);

	//1 - iii
	float x = 1; while(1+x/2!=1) {x/=2;}
	printf("%g (while method)\n", x);
	x = 1; do{x/=2;}while(1+x/2!=1);
	printf("%g (dowhile method)\n", x);
	for (x = 1; 1+x/2!=1; x/=2) {}
	printf("%g (forloop method)\n", x);
	printf("%g (FLT_EPSILON)\n\n",FLT_EPSILON);

	double y = 1; while(1+y/2!=1) {y/=2;}
	printf("%g (while method)\n", y);
	y = 1; do{y/=2;}while(1+y/2!=1);
	printf("%g (dowhile method)\n", y);
	for (y = 1; 1+y/2!=1; y/=2) {}
	printf("%g (forloop method)\n", y);
	printf("%g (DBL_EPSILON)\n\n",DBL_EPSILON);

	long double z = 1; while(1+z/2!=1) {z/=2;}
	printf("%Lg (while method)\n", z);
	z = 1; do{z/=2;}while(1+z/2!=1);
	printf("%Lg (dowhile method)\n", z);
	for (z = 1; 1+z/2!=1; z/=2) {}
	printf("%Lg (forloop method)\n", z);
	printf("%Lg (LDBL_EPSILON)\n\n",LDBL_EPSILON);
	
	//2 - i
	int max = INT_MAX/2;
	float sum_up_float = 0;
	for (int i = 1; i < max; ++i) {sum_up_float+=1./i;}
	printf("%g (sum_up_float)\n", sum_up_float);
	float sum_down_float = 0;
	for (int i = max; i > 0; --i) {sum_down_float+=1./i;}
	printf("%g (sum_down_float)\n\n", sum_down_float);

	//2 - ii
	printf("For the up-sum the smallest numbers get rounded when added to a big number\n\n");

	//2 - iii
	printf("The sums converge when max is big enough that the smallest numbers gets rounded to 0 when added to the sum\n\n");
	
	//2 - iiii
	double sum_up_double = 0;
	for (int i = 1; i < max; ++i) {sum_up_double+=1./i;}
	printf("%.20g (sum_up_double)\n", sum_up_double);
	double sum_down_double = 0;
	for (int i = max; i > 0; --i) {sum_down_double+=1./i;}
	printf("%.20g (sum_down_double)\n\n", sum_down_double);
	
	printf("The problem  persists, but is now much less significant\n\n");
	
	//3
	printf("equal(1,1,1,1): %i\n",equal(1,1,1,1));
	return 0;
}
