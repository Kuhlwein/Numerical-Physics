#include<stdio.h>
#include"komplex.h"

void komplex_print (char *s, komplex a) {
	printf ("%s (%g,%g)\n", s, a.re, a.im);
}

komplex komplex_new (double x, double y) {
	komplex z = { x, y };
	return z;
}

void komplex_set (komplex* z, double x, double y) {
	(*z).re = x;
	(*z).im = y;
}

komplex komplex_add (komplex a, komplex b) {
	komplex result = { a.re + b.re , a.im + b.im };
	return result;
}

komplex komplex_sub (komplex a, komplex b) {
	komplex result = { a.re - b.re , a.im - b.im };
	return result;
}


komplex komplex_mul (komplex a, komplex b) {
	komplex result = {a.re*b.re - a.im*b.im , a.re*b.im + a.im*b.re};
	return result;
}

komplex komplex_conjugate (komplex a) {
	komplex result = {a.re , -a.im};
	return result;
}

komplex komplex_div (komplex a, komplex b) {
	a = komplex_mul(a,komplex_conjugate(b));
	b = komplex_mul(b,komplex_conjugate(b));
	komplex result = {a.re/b.re , a.im/b.re};
	return result;
}

