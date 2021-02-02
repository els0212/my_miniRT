#include "ft_ray_hit_2.h"

t_vector	*ft_get_normal(t_vector hit_point, t_object obj)
{
	t_vector	pc;

	if (obj.id == SPHERE)
		return (ft_vec_dup(ft_normalize(ft_vec_sub(hit_point, *obj.vec))));
	else if (obj.id == PLANE || obj.id == SQUARE)
		return (ft_vec_dup(*obj.dir));
	else if (obj.id == CYLINDER)
	{
		pc = ft_vec_sub(hit_point, *obj.vec);
		return (ft_vec_dup(ft_normalize(ft_vec_sub(hit_point,
						ft_vec_add(*obj.vec, ft_vec_mult_const(*obj.dir,
								ft_dot_product(*obj.dir, pc)))))));
	}
	else if (obj.id == TRIANGLE)
		return (ft_vec_dup(ft_normalize(ft_cross_product(
							ft_vec_sub(*obj.vec_third, *obj.vec),
				ft_vec_sub(*obj.vec_second, *obj.vec)))));
	else
		return (0);
}

t_vector	ft_get_discriminant(t_object *cylinder, t_ray *ray,
		double *discriminant, double *t)
{
	t_vector	oc;
	t_vector	h;
	double		a;
	double		b;
	double		c;

	oc = ft_vec_sub(*ray->origin, *cylinder->vec);
	h = ft_normalize(ft_vec_sub(ft_vec_add(*cylinder->vec,
					ft_vec_mult_const(*cylinder->dir,
						cylinder->height)), *cylinder->vec));
	a = ft_dot_product(*ray->dir, *ray->dir) -
		pow(ft_dot_product(*ray->dir, h), 2);
	b = 2.0 * (ft_dot_product(oc, *ray->dir) -
			ft_dot_product(*ray->dir, h) * ft_dot_product(oc, h));
	c = ft_dot_product(oc, oc) - pow(ft_dot_product(oc, h), 2)
		- pow((cylinder->dia / 2), 2);
	*discriminant = b * b - 4 * a * c;
	t[0] = (-b - sqrt(*discriminant)) / (2 * a);
	t[1] = (-b + sqrt(*discriminant)) / (2 * a);
	return (h);
}

int			ft_ray_hit_cylinder(t_object *cylinder, t_ray *ray)
{
	t_vector	h;
	t_vector	p[2];
	double		t[2];
	double		discriminant;
	double		height[2];

	h = ft_get_discriminant(cylinder, ray, &discriminant, t);
	if (discriminant >= 0)
	{
		if (t[0] < 0 || t[1] < 0)
			return (0);
		p[0] = ft_ray_at(*ray, t[0]);
		p[1] = ft_ray_at(*ray, t[1]);
		height[0] = ft_dot_product(ft_vec_sub(p[0], *cylinder->vec), h);
		height[1] = ft_dot_product(ft_vec_sub(p[1], *cylinder->vec), h);
		if ((height[0] > 0 && height[0] < cylinder->height &&
					ft_ray_change_hit(ray, t[0], cylinder)) ||
				(height[1] > 0 && height[1] <= cylinder->height &&
				ft_ray_change_hit(ray, t[1], cylinder)))
			return (1);
	}
	return (0);
}

int			ft_chk_intersect(t_object *obj, t_ray *ray)
{
	t_object	*now;

	now = obj;
	while (now)
	{
		if (now->id == PLANE && ft_ray_hit_plane(now, ray, 0) > 0)
			return (1);
		if (now->id == SPHERE && ft_ray_hit_sphere(now, ray, 0) > 0)
			return (1);
		if (now->id == SQUARE && ft_ray_hit_square(now, ray) > 0)
			return (1);
		if (now->id == TRIANGLE && ft_ray_hit_triangle(now, ray, 0) > 0)
			return (1);
		if (now->id == CYLINDER && ft_ray_hit_cylinder(now, ray) > 0)
			return (1);
		now = now->next;
	}
	return (0);
}

t_color		*ft_ray_color(t_ray *ray, t_object *obj)
{
	t_color		*ret;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	ft_color_cpy(ret, ft_color_init(0, 0, 0));
	while (obj)
	{
		if (obj->id == PLANE && ft_ray_hit_plane(obj, ray, 0) > 0)
			ft_color_cpy(ret, *obj->color);
		if (obj->id == SPHERE && ft_ray_hit_sphere(obj, ray, 0) > 0)
			ft_color_cpy(ret, *obj->color);
		if (obj->id == SQUARE && ft_ray_hit_square(obj, ray) > 0)
			ft_color_cpy(ret, *obj->color);
		if (obj->id == TRIANGLE && ft_ray_hit_triangle(obj, ray, 0) > 0)
			ft_color_cpy(ret, *obj->color);
		if (obj->id == CYLINDER && ft_ray_hit_cylinder(obj, ray) > 0)
			ft_color_cpy(ret, *obj->color);
		obj = obj->next;
	}
	ray->hit_norm = ray->ray_hit ?
		ft_get_normal(*ray->hit_point, *ray->hit_obj) : 0;
	if (ray->hit_norm && ft_dot_product(*ray->hit_norm, *ray->dir) > 0)
		ft_vec_cpy(ray->hit_norm, ft_vec_mult_const(*ray->hit_norm, -1));
	return (ret);
}
