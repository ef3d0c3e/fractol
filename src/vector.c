#include "vector.h"

inline void
vec_add(t_vec2d *a, const t_vec2d *const b)
{
	a->x += b->x;
	a->y += b->y;
}

inline void
vec_mul(t_vec2d *a, const double f)
{
	a->x *= f;
	a->y *= f;
}

inline void
vec_apply(t_vec2d *a, double(*fn)(const double x))
{
	a->x = fn(a->x);
	a->y = fn(a->y);
}
