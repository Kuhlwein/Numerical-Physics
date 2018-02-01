#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

int main(int argc, char *argv[])
{
	int i=1; while(i+1>i) {++i;}
	printf("max int while:   %i\n",i);

	i=1; do{++i;}while(i+1>i);
	printf("max int dowhile: %i\n",i);

	for (i = 0; i < i+1; ++i) {}
	printf("max int for:     %i\n",i);

	printf("INT_MAX:         %i\n\n", INT_MAX);


	i=1; while(i>i-1) {--i;}
	printf("min int while:   %i\n",i);

	i=1; do{--i;}while(i>i-1);
	printf("min int dowhile: %i\n",i);

	for (i = 0; i-1 < i; --i) {}
	printf("min int for:     %i\n",i);

	printf("INT_MIN:         %i\n\n", INT_MIN);

	return 0;
}
