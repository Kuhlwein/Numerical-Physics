#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	double x;
	while( scanf("%lg",&x) != EOF) printf("%lg \t %lg\n",x,cos(x));
	return 0;
}
