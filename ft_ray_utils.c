#include "minirt.h"

t_ray	*ft_ray_init(t_vector *origin, t_vector dir)
{
	t_ray		*ret;
	t_vector	*hit_point;

	if (!(hit_point = (t_vector *)malloc(sizeof(t_vector))) || !(ret = (t_ray *)malloc(sizeof(t_ray))))
		return (0);
	ret->origin = ft_vec_dup(*origin);
	ret->dir = ft_vec_dup(dir);
	ft_vector_init(hit_point, RAYMAX, RAYMAX, RAYMAX);
	ret->hit_point = hit_point;
	ret->ray_hit = 0;
	return (ret);
}

t_vector	ft_ray_at(t_ray ray, double d)
{
	return (ft_vec_add(*ray.origin,
				ft_vec_product_const(*ray.dir, d)));
}
int			ft_ray_change_hit(t_ray *ray, int t)
{
	t_vector	now;
	
	now = ft_vec_add(*ray->origin, ft_vec_product_const(*ray->dir, t));
	if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
	{
		free(ray->hit_point);
		ray->hit_point = ft_vec_dup(now);
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

int			ft_ray_hit_sphere(t_object *sphere, t_ray *ray, int t)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	//t_vector	now;

	while (t <= RAYMAX)
	{
		oc = ft_vec_sub(*ray->origin, *sphere->vec);
		a = t * t * ft_dot_product(*ray->dir, *ray->dir);
		b = 2.0 * t * ft_dot_product(oc, *ray->dir);
		c = ft_dot_product(oc, oc) - (sphere->dia / 2) * (sphere->dia / 2);
		if ((b * b - 4 * a * c) > EPSILON && ft_ray_change_hit(ray, t))
			return (1);
		//printf("det = %f, ret = %d\n", discriminant, discriminant > 0 ? 1 : 0);
		//return (discriminant > 0 ? 1 : 0);
		t++;
	}
	return (0);
}

int			ft_ray_hit_plane(t_object *plane, t_ray *ray, int t)
{
	double		denom;
	t_vector	oc;
	
	denom = ft_dot_product(*plane->dir, *ray->dir);
	//printf("denom = %f\n",denom);
	if (denom > EPSILON)// && ft_ray_change_hit(ray, t))
	{
		ft_vec_cpy(&oc, ft_vec_sub(*plane->vec, *ray->origin));
		t = ft_dot_product(oc, *plane->dir) / denom;
		if (t >= 0 && ft_ray_change_hit(ray, t) > 0)
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
	double	tmin[3];
	double	tmax[3];
	t_vector	default_n;
	double	r[3][3];
	double	axis[3];
	double	new_axis[3];
	//t_vector	vup;
	//t_vector	u;
	//t_vector	v;

	ft_vector_init(&default_n, 0, 0, 1.0);
	//u = ft_cross_product(vup, *square->dir);
	double angle = acos((ft_dot_product(default_n, *square->dir) / (1 * sqrt(pow(square->dir->x, 2) + pow(square->dir->y, 2) + pow(square->dir->z, 2)))));
	printf("cos(angle) = %.6lf\n", cos(angle));
	//v = ft_cross_product(u, *square->dir);
	//printf("u.x = %.6lf, u.y = %.6lf, u.z = %.6lf, v.x = %.6lf, v.y = %.6lf, v.z = %.6lf\n",\
	//		u.x, u.y, u.z, v.x, v.y, v.z);

	// init Rotation matrix
	r[0][0] = cos(angle) + square->dir->x * square->dir->x * (1 - cos(angle));
	r[0][1] = square->dir->x * square->dir->y * (1 - cos(angle)) - square->dir->z * sin(angle);
	r[0][2] = square->dir->x * square->dir->z * (1 - cos(angle)) + square->dir->y * sin(angle);
	r[1][0] = square->dir->y * square->dir->z * (1 - cos(angle)) + square->dir->z * sin(angle);
	r[1][1] = cos(angle) + square->dir->y * square->dir->y * (1 - cos(angle));
	r[1][2] = square->dir->y * square->dir->z * (1 - cos(angle)) + square->dir->x * sin(angle);
	r[2][0] = square->dir->z * square->dir->x * (1 - cos(angle)) + square->dir->y * sin(angle);
	r[2][1] = square->dir->z * square->dir->y * (1 - cos(angle)) + square->dir->x * sin(angle);
	r[2][2] = cos(angle) + square->dir->z * square->dir->z * (1 - cos(angle));
	// end

	//rotate x, y, z
		axis[0] = square->vec->x - square->size / 2;
		axis[1] = square->vec->y - square->size / 2;
		axis[2] = square->vec->z - square->size / 2;
		new_axis[0] = r[0][0] * axis[0] + r[0][1] * axis[1] + r[0][2] * axis[2];
		new_axis[1] = r[1][0] * axis[0] + r[1][1] * axis[1] + r[1][2] * axis[2];
		new_axis[2] = r[2][0] * axis[0] + r[2][1] * axis[1] + r[2][2] * axis[2];
		pirntf("before x = %.6lf, y = %.6lf, z = %.6lf\n",axis[0], axis[1], axis[2]);
		pirntf("after x = %.6lf, y = %.6lf, z = %.6lf\n",new_axis[0], new_axis[1], new_axis[2]);
	//end

	tmin[0] = ((square->vec->x - (square->size / 2)) - ray->origin->x) / ray->dir->x;
	tmax[0] = ((square->vec->x + square->size / 2) - ray->origin->x) / ray->dir->x;
	//printf("square.x.min = %.6lf, tmin[0] = %.6lf\n", square->vec->x - square->size / 2, tmin[0]);
	//printf("ray.ori.x = %.6lf, ray.dir.x = %.6lf\n", ray->origin->x, ray->dir->x);
	if (tmin[0] > tmax[0])
		ft_swap(&tmin[0], &tmax[0]);
	tmin[1] = ((square->vec->y - square->size / 2) - ray->origin->y) / ray->dir->y;
	tmax[1] = ((square->vec->y + square->size / 2) - ray->origin->y) / ray->dir->y;
	if (tmin[1] > tmax[1])
		ft_swap(&tmin[1], &tmax[1]);
//	printf("tmin[0] = %.6lf, tmax[0]=%.6lf, tmin[1] = %.6lf, tmax[1] = %.6lf\n", tmin[0], tmax[0], tmin[1], tmax[1]);
	// default
	if ((tmin[0] > tmax[1]) || (tmin[1] > tmax[0]))
		return (0);
	tmin[0] = (tmin[1] > tmin[0]) ? tmin[1] : tmin[0];
	tmax[0] = (tmax[1] < tmax[0]) ? tmax[1] : tmax[0];
	tmin[2] = ((square->vec->z - square->size / 2) - ray->origin->z) / ray->dir->z;
	tmax[2] = ((square->vec->z + square->size / 2) - ray->origin->z) / ray->dir->z;
	// default
	if (tmin[2] > tmax[2])
		ft_swap(&tmin[2], &tmax[2]);
	if ((tmin[0] > tmax[2]) || (tmin[2] > tmax[0]))
		return (0);
	//printf("tmin[0] = %.6lf, tmax[0] = %.6lf, tmin[2] = %.6lf, tmax[2] = %.6lf\n", tmin[0], tmax[0], tmin[2], tmax[2]);
	tmin[0] = (tmin[2] > tmin[0]) ? tmin[2] : tmin[0];
	tmax[0] = (tmax[2] < tmax[0]) ? tmax[2] : tmax[0];
	//printf("tmin = %.6lf, tmax = %.6lf\n", tmin[0], tmax[0]);
	if (tmin[0] < -RAYMAX || tmax[0] > RAYMAX)
		return (0);
	return (1);
}

int			ft_triangle_inside_outside(t_vector p, t_vector a, t_vector b, t_vector n)
{
	t_vector	edge;
	t_vector	p_edge;

	edge = ft_vec_sub(a, b);
	p_edge = ft_vec_sub(p, b);
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
	discriminant = ft_dot_product(n, *ray->dir);
	//printf("discriminant = %.6lf\n", discriminant);
	if (fabs(discriminant) < EPSILON)
		return (0);
	t = (ft_dot_product(n, *ray->origin) + ft_dot_product(n, *triangle->vec)) / discriminant;
	if (t < 0)
		return (0);
	p = ft_ray_at(*ray, t);
	if (ft_triangle_inside_outside(p, *triangle->vec, *triangle->vec_second, n) == 0)
		return (0);
	else if (ft_triangle_inside_outside(p, *triangle->vec_second, *triangle->vec_third, n) == 0)
		return (0);
	else if (ft_triangle_inside_outside(p, *triangle->vec_third, *triangle->vec, n) == 0)
		return (0);
	return (1);
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
	ret->red = 255;
	ret->green = 255;
	ret->blue = 255;
	//printf("ray_st = %d\n", ray_st);
	//printf("ori x = %f, y = %f, z = %f\n",ray->origin->x, ray->origin->y, ray->origin->z);
	//printf("now x = %f, y = %f, z = %f\n",now.x, now.y, now.z);
	now_obj = obj;
	while (now_obj)
	{
		id = now_obj->id;
		//printf("id = %d\n", id);
		if (id == PLANE && ft_ray_hit_plane(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, now_obj->color);
		if (id == SPHERE && ft_ray_hit_sphere(now_obj, ray, 0) > 0)
			ft_color_cpy(ret, now_obj->color);
		if (id == SQUARE && ft_ray_hit_square(now_obj, ray) > 0)
				ft_color_cpy(ret, now_obj->color);
		if (id == TRIANGLE && ft_ray_hit_triangle(now_obj, ray, 0) > 0)
				ft_color_cpy(ret, now_obj->color);
		now_obj = now_obj->next;
	}
	return (ret);
}
