#include "nvector.h"
#include <stdio.h>
#include <stdlib.h>
#include "equal.h"

#define RND (double)rand()/RAND_MAX


int main()
{
	int n = 5;
	
	//nvector_alloc
	nvector *v = nvector_alloc(n);

	printf("\ntesting nvector_alloc...\n");
	if (v == NULL) printf("test failed\n");
	else printf("test passed\n");
	
	//nvector_set/get
	double value = RND;
	int i = n / 2;
	nvector_set(v, i, value);
	double vi = nvector_get(v, i);

	printf("\ntesting nvector_set and nvector_get...\n");
	if (double_equal(vi, value)) printf("test passed\n");
	else printf("test failed\n");
	
	//nevector add
	nvector *a = nvector_alloc(n);
	nvector *b = nvector_alloc(n);
	nvector *c = nvector_alloc(n);
	for (int i = 0; i < n; i++) {
		double x = RND, y = RND;
		nvector_set(a, i, x);
		nvector_set(b, i, y);
		nvector_set(c, i, x + y);
	}
	nvector_add(a, b);

	printf("\ntesting nvector_add...\n");
	nvector_print("a+b should   = ", c);
	nvector_print("a+b actually = ", a);
	if (nvector_equal(c, a)) printf("test passed\n");
	else printf("test failed\n");

	//nevector sub
	for (int i = 0; i < n; i++) {
		double x = RND, y = RND;
		nvector_set(a, i, x);
		nvector_set(b, i, y);
		nvector_set(c, i, x - y);
	}
	nvector_sub(a, b);

	printf("\ntesting nvector_sub...\n");
	nvector_print("a-b should   = ", c);
	nvector_print("a-b actually = ", a);
	if (nvector_equal(c, a)) printf("test passed\n");
	else printf("test failed\n");

	//nevector dot
	double dotShould = 0;
	for (int i = 0; i < n; i++) {
		double x = RND, y = RND;
		nvector_set(a, i, x);
		nvector_set(b, i, y);
		dotShould =+ x*y;
	}
	double dotActually = nvector_dot_product(a, b);

	printf("\ntesting nvector_dot...\n");
	printf("a*b should   = %f\n", dotShould);
	printf("a*b actually = %f\n", dotActually);
	if (double_equal(dotShould,dotActually)) printf("test passed\n");
	else printf("test failed\n");

	nvector_free(v);
	nvector_free(a);
	nvector_free(b);
	nvector_free(c);
	return 0;
}
