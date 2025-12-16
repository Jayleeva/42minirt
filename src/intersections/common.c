#include "../inc/minirt.h"

float	find_t(float discr, float half_b, float a, int sign)
{
	float	t;

	t = -1;
	if (sign == 0)
		t = (-half_b - sqrtf(discr)) / a;
	else if (sign == 1)
		t = (-half_b + sqrtf(discr)) / a;
	return (t);
}