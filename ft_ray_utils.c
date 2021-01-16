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
		if ((b * b - 4 * a * c) > 0.0 && ft_ray_change_hit(ray, t))
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
	if (denom > 0.0f)// && ft_ray_change_hit(ray, t))
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

void		ft_sqaure_t_range(double *min, double *max, double origin, double dir)
{
	double	temp;

	*min = (*min - origin) / dir;
	*max = (*max - origin) / dir;
	if (dir < 0)
	{
		temp = *min;
		*min = *max;
		*max = temp;
	}
}

int			ft_ray_hit_square(t_object *square, t_ray *ray, int t)
{
	double	tmin[3];
	double	tmax[3];

	ft_square_t_range(&(tmin[0] = square->vec->x - square->size / 2),
			&(tmax[0] = square->vec->x + square->size / 2), ray->origin->x, ray->dir->x);
	ft_square_t_range(&(tmin[1] = square->vec->y - square->size / 2),
			&(tmax[1] = square->vec->y + square->size / 2), ray->origin->y, ray->dir->y);
	ft_square_t_range(&(tmin[2] = square->vec->z - square->size / 2),
			&(tmax[2] = square->vec->z + square->size / 2), ray->origin->z, ray->dir->z);
	if ((tmin[0] > tmax[1]) || (tmin[0] > tmax[2]) || (tmin[1] > tmax[0]) ||
			(tmin[1] > tmax[2]) || (tmin[2] > tmax[0]) || (tmin[2] > tmax[1]))
		return (0);
	if (tmin[1] > tmin[0])
		tmin[0] = tmin[1];
	if (
	if (tymax < txmax)
		txmax = tymax;
		return (0);
}

t_color		*ft_ray_color(t_ray *ray, t_object *obj)
{
	t_color		*ret;
	int			ray_st;
	double		discriminant;
	t_vector	now;
	int			id;
	t_object	*now_obj;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	// ray_st doesn't need to run loop
	// sphere needs ray_st loop
	// plane can return ray_st => need to check 0 <= ray_st <= raymax
	// square uses aabb intersection algorithm
		//printf("ray_st = %d\n", ray_st);
		//printf("ori x = %f, y = %f, z = %f\n",ray->origin->x, ray->origin->y, ray->origin->z);
		//printf("now x = %f, y = %f, z = %f\n",now.x, now.y, now.z);
	//ray_st = 0;
	//now = ft_vec_add(*ray->origin, ft_vec_product_const(*ray->dir, ray_st));
	//if (ft_get_dist(*ray->origin, *ray->hit_point) <= ft_get_dist(*ray->origin, now))
	//	break ;
	//else
	//{
		now_obj = obj;
		while (now_obj)
		{
			id = now_obj->id;
			//printf("id = %d\n", id);
			//sphere need to add the loop ray_at <= RAYMAX
			if (id == SPHERE && ft_ray_hit_sphere(now_obj, ray, 0) > 0)
				ft_color_cpy(ret, now_obj->color);
				//ft_ray_hit_sphere(now_obj, ray, 0);
				/*
				if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
				{
					free(ray->hit_point);
					ray->hit_point = ft_vec_dup(now);
					ft_color_cpy(ret, now_obj->color);
					return (ret);
				}
				*/
			if (id == PLANE && ft_ray_hit_plane(now_obj, ray, 0) > 0)
				ft_color_cpy(ret, now_obj->color);
				/*
				printf("plane?!\n");
				if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
				{
					free(ray->hit_point);
					ray->hit_point = ft_vec_dup(now);
					ft_color_cpy(ret, now_obj->color);
					return (ret);
				}
				*/
			if (id == SQUARE && ft_ray_hit_square(now_obj, ray, 0) > 0)
				ft_color_cpy(ret, now_obj->color);
			now_obj = now_obj->next;
		}
		//}
	ret->red = 10;
	ret->green = 10;
	ret->blue = 10;
	return (ret);
}
