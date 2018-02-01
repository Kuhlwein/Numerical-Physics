#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

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
	return 0;
}
