#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	double x;
	for (int i = 1; i < argc; ++i) {
		x = atof(argv[i]);
		printf("%lg \t %lg\n", x,sin(x));
	}
	return 0;
}
