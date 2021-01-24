#include "minirt.h"

t_ray	*ft_ray_init(t_vector *origin, t_vector dir)
{
	t_ray		*ret;
	t_vector	*hit_point;

	if (!(hit_point = (t_vector *)malloc(sizeof(t_vector))) || !(ret = (t_ray *)malloc(sizeof(t_ray))))
		return (0);
	ret->origin = ft_vec_dup(*origin);
	//t_vector test = ft_vec_sub(dir, *origin);
	//printf("test x = %f y = %f z = %f\n", test.x, test.y, test.z);
	ret->dir = ft_vec_dup(ft_vec_sub(dir, *origin));//ft_vec_dup(ft_normalize(ft_vec_sub(dir, *origin)));
	ft_vector_init(hit_point, RAYMAX, RAYMAX, RAYMAX);
	ret->hit_point = hit_point;
	ret->hit_obj = 0;
	ret->hit_norm = 0;
	ret->ray_hit = 0;
	return (ret);
}

t_vector	ft_ray_at(t_ray ray, double d)
{
	return (ft_vec_add(*ray.origin,
				ft_vec_product_const(*ray.dir, d)));
}

t_vector	*ft_get_normal(t_vector hit_point, t_object obj)
{
	t_vector	pc;
	//printf("get normal ! \n");
	if (obj.id == SPHERE)
		return (ft_vec_dup(ft_normalize(ft_vec_sub(hit_point, *obj.vec))));
	else if (obj.id == PLANE || obj.id == SQUARE)
		return (ft_vec_dup(*obj.dir));
	else if (obj.id == CYLINDER)
	{
		pc = ft_vec_sub(hit_point, *obj.vec);
		return (ft_vec_dup(ft_normalize(ft_vec_sub(hit_point, 
						ft_vec_product_const(*obj.dir, ft_dot_product(*obj.dir, pc))))));
	}
	else
		return (ft_vec_dup(ft_cross_product(ft_vec_sub(*obj.vec_third, *obj.vec),
				ft_vec_sub(*obj.vec_second, *obj.vec))));
}

int			ft_ray_change_hit(t_ray *ray, int t, t_object *hit_obj)
{
	t_vector	now;
	
	now = ft_vec_add(*ray->origin, ft_vec_product_const(*ray->dir, t));
	//printf("id = %d, t = %d, hit\n",hit_obj->id, t);
	if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
	{
		free(ray->hit_point);
		ray->hit_point = ft_vec_dup(now);
		ray->hit_obj = hit_obj;
		ray->ray_hit = 1;
		return (1);
	}
	return (0);
}
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

	//printf("ori x =%.6f, y=%.6f, z=%.6f\n",ray->origin->x, ray->origin->y, ray->origin->z);
	//printf("sph x =%.6f, y=%.6f, z=%.6f\n",sphere->vec->x, sphere->vec->y, sphere->vec->z);
	oc = ft_vec_sub(*ray->origin, *sphere->vec);
	a = ft_dot_product(*ray->dir, *ray->dir);
	//printf("ray x =%.6f, y=%.6f, z=%.6f\n",ray->dir->x, ray->dir->y, ray->dir->z);
	b = 2.0 * ft_dot_product(*ray->dir, oc);
	c = ft_dot_product(oc, oc) - pow((sphere->dia / 2), 2);
	discriminant = b * b - 4 * a * c;
	//printf("b = %f c = %f det = %f\n", b, c, discriminant);
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
		//printf("a = %.6lf, b = %.6lf, t = %.6lf\n", a,b,t);
		//printf("bef hit\n");
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
	//printf("denom = %f\n",denom);
	if (fabs(denom) > EPSILON)// && ft_ray_change_hit(ray, t))
	{
		ft_vec_cpy(&oc, ft_vec_sub(*plane->vec, *ray->origin));
		t = ft_dot_product(oc, *plane->dir) / denom;
		if (t >= 0 && ft_ray_change_hit(ray, t, plane) > 0)
			return (1);
		/*
		//printf("oc.x = %f y = %f, z = %f\n", oc.x,oc.y,oc.z);
		if (discriminant == t)
			return (1);
		*/
	}
	return (0);
}

void		ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int			ft_ray_hit_square(t_object *square, t_ray *ray)
{
	double		denom;
	t_vector	oc;
	t_vector	p;
	double		t;
	
	denom = ft_dot_product(*square->dir, *ray->dir);
	//printf("denom = %f\n", denom);
	if (fabs(denom) > EPSILON)
	{
		ft_vec_cpy(&oc, ft_vec_sub(*square->vec, *ray->origin));
		t = ft_dot_product(oc, *square->dir) / denom;
		//printf("t = %f\n", t);
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

int			ft_triangle_inside_outside(t_vector p, t_vector a, t_vector b, t_vector n)
{
	t_vector	edge;
	t_vector	p_edge;

	edge = ft_vec_sub(a, b);
	p_edge = ft_vec_sub(p, b);
	//printf("io prob?\n");
	if (ft_dot_product(ft_cross_product(edge, p_edge), n) < 0)
		return (0);
	return (1);
}

int			ft_ray_hit_triangle(t_object *triangle, t_ray *ray, int t)
{
	t_vector	a;
	t_vector	b;
	t_vector	p;
	t_vector	n;
	double		discriminant;

	a = ft_vec_sub(*triangle->vec_third, *triangle->vec);
	b = ft_vec_sub(*triangle->vec_second, *triangle->vec);
	n = ft_cross_product(a, b);
	//printf("n.x = %f y= %f z = %f\n",n.x,n.y, n.z);
	discriminant = ft_dot_product(n, *ray->dir);
	//printf("discriminant = %.6lf\n", discriminant);
	if (fabs(discriminant) < EPSILON)
		return (0);
	//printf("ray_dir x %f y %f z %f\n",ray->dir->x, ray->dir->y, ray->dir->z);
	//printf("n.ray = %lf, n.triangle = %lf\n", ft_dot_product(n, *ray->origin), ft_dot_product(n, *triangle->vec));
	t = (ft_dot_product(ft_vec_sub(*triangle->vec, *ray->origin), n) / discriminant);
	//t = (ft_dot_product(n, *ray->origin) + ft_dot_product(n, *triangle->vec)) / discriminant;
	//printf("t = %d\n", t);
	if (t < 0)
		return (0);
	p = ft_ray_at(*ray, t);
	/*
	printf("vec x = %f y = %f z = %f\n",triangle->vec->x, triangle->vec->y, triangle->vec->z);
	printf("vec2 x = %f y = %f z = %f\n",triangle->vec_second->x, triangle->vec_second->y, triangle->vec_second->z);
	printf("vec3 x = %f y = %f z = %f\n",triangle->vec_third->x, triangle->vec_third->y, triangle->vec_third->z);
	*/
	if (ft_triangle_inside_outside(p, *triangle->vec, *triangle->vec_second, n) == 0)
	{
		//printf("first ret\n");
		return (0);
	}
	else if (ft_triangle_inside_outside(p, *triangle->vec_second, *triangle->vec_third, n) == 0)
	{
		//printf("second ret\n");
		return (0);
	}
	else if (ft_triangle_inside_outside(p, *triangle->vec_third, *triangle->vec, n) == 0)
	{
		//printf("third ret\n");
		return (0);
	}
	if (ft_ray_change_hit(ray, t, triangle) > 0)
	{
		return (1);
	}
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
	double		discriminant;
	double		height;
	int			hit_flag;

	oc = ft_vec_sub(*ray->origin, *cylinder->vec); // w
	h = ft_vec_sub(ft_vec_add(*cylinder->vec, ft_vec_product_const(*cylinder->dir, cylinder->height)), *cylinder->vec);
	h_norm = ft_vec_div_const(h, sqrt(pow(h.x, 2) + pow(h.y, 2) + pow(h.z, 2)));
	//printf("h ! x = %f y  = %f z = %f\n", h.x, h.y, h.z);
	//printf("c ! x = %f y  = %f z = %f\n", cylinder->vec->x, cylinder->vec->y, cylinder->vec->z);
	//printf("h_norm ! x = %f y  = %f z = %f\n", h_norm.x, h_norm.y, h_norm.z);

	a = ft_dot_product(*ray->dir, *ray->dir) - pow(ft_dot_product(*ray->dir, h_norm), 2);
	b = 2.0 * (ft_dot_product(oc, *ray->dir) - ft_dot_product(*ray->dir, h_norm) * ft_dot_product(oc, h_norm));
	c = ft_dot_product(oc, oc) - pow(ft_dot_product(oc, h_norm), 2) - pow((cylinder->dia / 2), 2);
	//printf("dot(oc, oc) = %f pow(2) = %f\n",ft_dot_product(oc, oc), pow(ft_dot_product(oc, h_norm), 2));
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		// need to check t and t2..
		t = (-b - sqrt(discriminant)) / (2 * a);
		double t2;
		t2 = (-b + sqrt(discriminant)) / (2 * a);

		//printf("cylinder t = %f\n", t);
		if (t < 0 || t2 < 0)
			return (0);
		p = ft_ray_at(*ray, t);
		//printf("p x = %f y = %f z = %f\n", p.x, p.y, p.z);
		hit_flag = 0;
		height = ft_dot_product(ft_vec_sub(p, *cylinder->vec), h_norm);
		//printf("p x = %f y = %f z = %f\n", p.x, p.y, p.z);
		//printf("ht = %f, norm = %f\n", height, cylinder->height);
		//printf("a = %.6lf, b = %.6lf, t = %.6lf\n", a,b,t);
		if (height >= 0 && height <= cylinder->height)
			hit_flag = 1;
		p = ft_ray_at(*ray, t2);
		height = ft_dot_product(ft_vec_sub(p, *cylinder->vec), h_norm);
		if (height >= 0 && height <= cylinder->height)
			hit_flag = 1;
		if (hit_flag == 1 && ft_ray_change_hit(ray, t, cylinder))
			return (1);
	}
	return (0);
}

t_color		*ft_ray_color(t_ray *ray, t_object *obj)
{
	t_color		*ret;
	int			id;
	t_object	*now_obj;
	//t_vector	now;
	//double		discriminant;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	ret->red = 0;
	ret->green = 0;
	ret->blue = 0;
	//printf("ray_st = %d\n", ray_st);
	//printf("ori x = %f, y = %f, z = %f\n",ray->origin->x, ray->origin->y, ray->origin->z);
	//printf("now x = %f, y = %f, z = %f\n",now.x, now.y, now.z);
	now_obj = obj;
	while (now_obj)
	{
		id = now_obj->id;
	//	printf("id = %d\n", id);
		if (id == PLANE && ft_ray_hit_plane(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (id == SPHERE && ft_ray_hit_sphere(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (id == SQUARE && ft_ray_hit_square(now_obj, ray) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (id == TRIANGLE && ft_ray_hit_triangle(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, *now_obj->color);
		if (id == CYLINDER && ft_ray_hit_cylinder(now_obj, ray) > 0)
			ft_color_cpy(ret, *now_obj->color);
	//	printf("hit = %d\n", ray->ray_hit);
		now_obj = now_obj->next;
	}
	//printf("end loop!");
	ray->hit_norm = ray->ray_hit ? ft_get_normal(*ray->hit_point, *ray->hit_obj) : 0;
	if (ray->hit_norm && ft_dot_product(*ray->hit_norm, *ray->dir) > 0)
		ft_vec_cpy(ray->hit_norm, ft_vec_product_const(*ray->hit_norm, -1));

	//if (ray->ray_hit)
	//	printf("hit norm x = %f y = %f z = %f\n", ray->hit_norm->x, ray->hit_norm->y, ray->hit_norm->z);
	return (ret);
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
