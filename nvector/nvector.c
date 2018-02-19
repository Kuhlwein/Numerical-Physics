#include <stdio.h>
#include <stdlib.h>
#include "nvector.h"
#include "equal.h"

nvector* nvector_alloc(int n) {
  nvector* v = malloc(sizeof(nvector));
  (*v).size = n;
  (*v).data = malloc(n*sizeof(double));
  if( v==NULL ) fprintf(stderr,"error in nvector_alloc\n");
  return v;
}

void nvector_free(nvector* v) {
	free(v->data);
	free(v);
}

void nvector_set(nvector* v, int i, double value) {
	(*v).data[i]=value;
}

double nvector_get(nvector* v, int i) {
	return (*v).data[i];
}

void nvector_sub(nvector* a, nvector* b) {
	if( a->size != b->size ) fprintf(stderr,"error: cannot sub vectors of different sizes");
	double ai, bi;
	for (int i = 0; i < a->size; i++) {
		bi = nvector_get(b,i);
		ai = nvector_get(a,i);
		nvector_set(a,i,ai-bi);
	}
}

void nvector_add(nvector* a, nvector* b) {
	if( a->size != b->size ) fprintf(stderr,"error: cannot add vectors of different sizes");
	double ai, bi;
	for (int i = 0; i < a->size; i++) {
		bi = nvector_get(b,i);
		ai = nvector_get(a,i);
		nvector_set(a,i,ai+bi);
	}
}

double nvector_dot_product (nvector* a, nvector* b) {
	if( a->size != b->size ) fprintf(stderr,"error: cannot dot vectors of different sizes");
	double res = 0;
	for (int i = 0; i < a->size; i++) {
		res =+ nvector_get(b,i)*nvector_get(a,i);
	}
	return res;
}

int nvector_equal(nvector* a, nvector* b) {
	if( a->size != b->size ) return 0;
	double ai, bi;
	for (int i = 0; i < a->size; i++) {
		bi = nvector_get(b,i);
		ai = nvector_get(a,i);
		if (double_equal(ai,bi) == 0) return 0;
	}
	return 1;
}

void nvector_print(char* s, nvector* v) {
	printf("%s ",s);
	for (int i = 0; i < v->size; i++) printf("%f ",nvector_get(v,i));
	printf("\n");
}





