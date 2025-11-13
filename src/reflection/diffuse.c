#include "../inc/minirt.h"

/*
diffuse=k_d*I_L*cos(theta)

k_d = diffuse reflection coeff(between 0-1)
I_L = s_L.ratio
cos(theta) = v_dot(u, v) / v_dot(v_norm(u), v_norm(v))

1 * s_L.ratio * dot(N, L)

N = normale
L = direction vers la lumiere
*/
