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
		return (ft_vec_dup(ft_normalize(ft_cross_product(ft_vec_sub(*obj.vec_third, *obj.vec),
				ft_vec_sub(*obj.vec_second, *obj.vec)))));
	else
		return (0);
}

int			ft_ray_hit_cylinder(t_object *cylinder, t_ray *ray)
{
	t_vector	oc;
	t_vector	h;
	t_vector	h_norm;
	t_vector	p;
	double		a;
	double		b;
	double		c;
	double		t;
	double		t2;
	double		discriminant;
	double		height;
	int			hit_flag;

	oc = ft_vec_sub(*ray->origin, *cylinder->vec);
	h = ft_vec_sub(ft_vec_add(*cylinder->vec, ft_vec_mult_const(*cylinder->dir, cylinder->height)), *cylinder->vec);
	h_norm = ft_vec_div_const(h, sqrt(pow(h.x, 2) + pow(h.y, 2) + pow(h.z, 2)));
	a = ft_dot_product(*ray->dir, *ray->dir) - pow(ft_dot_product(*ray->dir, h_norm), 2);
	b = 2.0 * (ft_dot_product(oc, *ray->dir) - ft_dot_product(*ray->dir, h_norm) * ft_dot_product(oc, h_norm));
	c = ft_dot_product(oc, oc) - pow(ft_dot_product(oc, h_norm), 2) - pow((cylinder->dia / 2), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		// need to check t and t2..
		t = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (t < 0 || t2 < 0)
			return (0);
		p = ft_ray_at(*ray, t);
		hit_flag = 0;
		height = ft_dot_product(ft_vec_sub(p, *cylinder->vec), h_norm);
		if (height > 0 && height < cylinder->height)
			hit_flag = 1;
		p = ft_ray_at(*ray, t2);
		height = ft_dot_product(ft_vec_sub(p, *cylinder->vec), h_norm);
		if (height > 0 && height <= cylinder->height)
			hit_flag = 1;
		if (hit_flag == 1 && ft_ray_change_hit(ray, t, cylinder))
			return (1);
	}
	return (0);
}

int		ft_chk_intersect(t_object *obj, t_ray *ray)
{
	t_object	*now;

	now = obj;
	while(now)
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
	t_object	*now_obj;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	ft_color_cpy(ret, ft_color_init(0, 0, 0));
	now_obj = obj;
	while (now_obj)
	{
		if (now_obj->id == PLANE && ft_ray_hit_plane(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (now_obj->id == SPHERE && ft_ray_hit_sphere(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (now_obj->id == SQUARE && ft_ray_hit_square(now_obj, ray) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (now_obj->id == TRIANGLE && ft_ray_hit_triangle(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (now_obj->id == CYLINDER && ft_ray_hit_cylinder(now_obj, ray) > 0)
			ft_color_cpy(ret, *now_obj->color);
		now_obj = now_obj->next;
	}
	ray->hit_norm = ray->ray_hit ? ft_get_normal(*ray->hit_point, *ray->hit_obj) : 0;
	if (ray->hit_norm && ft_dot_product(*ray->hit_norm, *ray->dir) > 0)
			ft_vec_cpy(ray->hit_norm, ft_vec_mult_const(*ray->hit_norm, -1));
	return (ret);
}
