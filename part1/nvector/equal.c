#include "equal.h"
#include <math.h>
#include <float.h>

int double_equal(double d1, double d2) {
	return fabs(d1-d2) < DBL_EPSILON;
}
