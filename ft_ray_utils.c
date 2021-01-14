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

t_vector	ft_ray_at(t_ray *ray, double d)
{
	return (ft_vec_add(*ray->origin,
				ft_vec_product_const(*ray->dir, d)));
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
	double		discriminant;

	oc = ft_vec_sub(*ray->origin, *sphere->vec);
	a = t * t * ft_dot_product(*ray->dir, *ray->dir);
	b = 2.0 * t * ft_dot_product(oc, *ray->dir);
	c = ft_dot_product(oc, oc) - (sphere->dia / 2) * (sphere->dia / 2);
	discriminant = (b * b - 4 * a * c);
	//printf("det = %f, ret = %d\n", discriminant, discriminant > 0 ? 1 : 0);
	//return (discriminant > 0 ? 1 : 0);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_color		*ft_ray_color(t_ray *ray, t_object *obj)
{
	t_color		*ret;
	int			ray_st;
	double		discriminant;
	t_vector	now;

	ray_st = 0;
	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	while (ray_st < RAYMAX)
	{
		//printf("ray_st = %d\n", ray_st);
		//printf("ori x = %f, y = %f, z = %f\n",ray->origin->x, ray->origin->y, ray->origin->z);
		//printf("now x = %f, y = %f, z = %f\n",now.x, now.y, now.z);
		if ((discriminant = ft_ray_hit_sphere(obj, ray, ray_st)) > 0)
		{
			now = ft_vec_add(*ray->origin, ft_vec_product_const(*ray->dir, ray_st));
			if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
			{
				free(ray->hit_point);
				ray->hit_point = ft_vec_dup(now);
				ft_color_cpy(ret, obj->color);
				return (ret);
			}
		}
		ray_st++;
	}
	ret->red = 10;
	ret->green = 10;
	ret->blue = 10;
	return (ret);
}
