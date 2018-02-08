#include"komplex.h"
#include"stdio.h"
#define TINY 1e-6

int main(){
	komplex a = {1,2}, b = {3,4};

	printf("testing komplex_add...\n");
	komplex r = komplex_add(a,b);
	komplex R = {4,6};
	komplex_print("a=",a);
	komplex_print("b=",b);
	komplex_print("a+b should   = ", R);
	komplex_print("a+b actually = ", r);

	printf("\ntesting komplex_sub...\n");
	r = komplex_sub(a,b);
	R = komplex_new(-2,-2);
	komplex_print("a=",a);
	komplex_print("b=",b);
	komplex_print("a-b should   = ", R);
	komplex_print("a-b actually = ", r);

	printf("\ntesting komplex_mul...\n");
	r = komplex_mul(a,b);
	R = komplex_new(-5,10);
	komplex_print("a=",a);
	komplex_print("b=",b);
	komplex_print("a*b should   = ", R);
	komplex_print("a*b actually = ", r);

	printf("\ntesting komplex_conjugate...\n");
	r = komplex_conjugate(a);
	R = komplex_new(1,-2);
	komplex_print("a=",a);
	komplex_print("conjugate(a) should   = ", R);
	komplex_print("conjugate(a) actually = ", r);
	
	printf("\ntesting komplex_div...\n");
	r = komplex_div(a,b);
	R = komplex_new(11./25,2./25);
	komplex_print("a=",a);
	komplex_print("b=",b);
	komplex_print("a/b should   = ", R);
	komplex_print("a/b actually = ", r);
}


