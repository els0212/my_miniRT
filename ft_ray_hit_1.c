#include "ft_ray_hit_1.h"

/*
** oc = (A - C) vector
** a = t^2 * b dot b
** b = 2 * t * b dot oc
** c = oc dot oc - r^2
*/

int			ft_ray_hit_sphere(t_object *sphere, t_ray *ray, double t)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = ft_vec_sub(*ray->origin, *sphere->vec);
	a = ft_dot_product(*ray->dir, *ray->dir);
	b = 2.0 * ft_dot_product(*ray->dir, oc);
	c = ft_dot_product(oc, oc) - pow((sphere->dia / 2), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
		if (t >= 0 && ft_ray_change_hit(ray, t, sphere) > 0)
			return (1);
		t = (-b + sqrt(discriminant)) / (2 * a);
		if (t >= 0 && ft_ray_change_hit(ray, t, sphere) > 0)
			return (1);
	}
	return (0);
}

int			ft_ray_hit_plane(t_object *plane, t_ray *ray, int t)
{
	double		denom;
	t_vector	oc;

	denom = ft_dot_product(*plane->dir, *ray->dir);
	if (fabs(denom) > EPSILON)
	{
		oc = ft_vec_sub(*plane->vec, *ray->origin);
		t = ft_dot_product(oc, *plane->dir) / denom;
		if (t >= 0 && ft_ray_change_hit(ray, t, plane) > 0)
			return (1);
	}
	return (0);
}

int			ft_ray_hit_square(t_object *square, t_ray *ray)
{
	double		denom;
	t_vector	oc;
	t_vector	p;
	double		t;

	denom = ft_dot_product(*square->dir, *ray->dir);
	if (fabs(denom) > EPSILON)
	{
		ft_vec_cpy(&oc, ft_vec_sub(*square->vec, *ray->origin));
		t = ft_dot_product(oc, *square->dir) / denom;
		if (t >= 0)
		{
			p = ft_ray_at(*ray, t);
			if (fabs(p.x - square->vec->x) > (square->size / 2))
				return (0);
			if (fabs(p.y - square->vec->y) > (square->size / 2))
				return (0);
			if (fabs(p.z - square->vec->z) > (square->size / 2))
				return (0);
			if (ft_ray_change_hit(ray, t, square) > 0)
				return (1);
		}
	}
	return (0);
}

int			ft_triangle_inside_outside(t_vector p,
		t_vector a, t_vector b, t_vector n)
{
	t_vector	edge;
	t_vector	p_edge;

	edge = ft_vec_sub(b, a);
	p_edge = ft_vec_sub(p, a);
	if (ft_dot_product(ft_cross_product(edge, p_edge), n) < 0)
		return (0);
	return (1);
}

int			ft_ray_hit_triangle(t_object *triangle, t_ray *ray, int t)
{
	t_vector	p;
	t_vector	n;
	double		discriminant;

	n = ft_normalize(ft_cross_product(
				ft_vec_sub(*triangle->vec_second, *triangle->vec),
				ft_vec_sub(*triangle->vec_third, *triangle->vec)));
	if (fabs(discriminant = ft_dot_product(n, *ray->dir)) < EPSILON)
		return (0);
	if ((t = ft_dot_product(ft_vec_sub(*triangle->vec,
						*ray->origin), n) / discriminant) < 0)
		return (0);
	p = ft_ray_at(*ray, t);
	if (ft_triangle_inside_outside(p, *triangle->vec,
				*triangle->vec_second, n) == 0)
		return (0);
	else if (ft_triangle_inside_outside(p, *triangle->vec_second,
				*triangle->vec_third, n) == 0)
		return (0);
	else if (ft_triangle_inside_outside(p, *triangle->vec_third,
				*triangle->vec, n) == 0)
		return (0);
	if (ft_ray_change_hit(ray, t, triangle) > 0)
		return (1);
	return (0);
}
