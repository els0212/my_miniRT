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

int			ft_ray_hit_plane(t_object *plane, t_ray *ray, int t)
{
	double		denom;
	t_vector	oc;
	double		discriminant;
	
	denom = ft_dot_product(*plane->dir,*ray->dir);
	//printf("denom = %f\n",denom);
	if (denom > 0.00001f)
	{
		ft_vec_cpy(&oc, ft_vec_sub(*plane->vec, *ray->origin));
		//printf("oc.x = %f y = %f, z = %f\n", oc.x,oc.y,oc.z);
		discriminant = ft_dot_product(oc, *plane->dir);
		if (discriminant == t)
			return (1);
	}
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

	ray_st = 0;
	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	// ray_st doesn't need to run loop
	// sphere needs ray_st loop
	// plane can return ray_st => need to check 0 <= ray_st <= raymax
	// square uses aabb intersection algorithm
	while (ray_st < RAYMAX)
	{
		//printf("ray_st = %d\n", ray_st);
		//printf("ori x = %f, y = %f, z = %f\n",ray->origin->x, ray->origin->y, ray->origin->z);
		//printf("now x = %f, y = %f, z = %f\n",now.x, now.y, now.z);
		now = ft_vec_add(*ray->origin, ft_vec_product_const(*ray->dir, ray_st));
		if (ft_get_dist(*ray->origin, *ray->hit_point) <= ft_get_dist(*ray->origin, now))
			break ;
		else
		{
			now_obj = obj;
			while (now_obj)
			{
				id = now_obj->id;
				//printf("id = %d\n", id);
				if (id == SPHERE && (discriminant = ft_ray_hit_sphere(now_obj, ray, ray_st)) > 0)
				{
					if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
					{
						free(ray->hit_point);
						ray->hit_point = ft_vec_dup(now);
						ft_color_cpy(ret, now_obj->color);
						return (ret);
					}
				}
				if (id == PLANE && (discriminant = ft_ray_hit_plane(now_obj, ray, ray_st)) > 0)
				{
					//printf("plane?!\n");
					if (ft_get_dist(*ray->origin, *ray->hit_point) > ft_get_dist(*ray->origin, now))
					{
						free(ray->hit_point);
						ray->hit_point = ft_vec_dup(now);
						ft_color_cpy(ret, now_obj->color);
						return (ret);
					}
				}
				now_obj = now_obj->next;
			}
		}
		ray_st++;
	}
	ret->red = 10;
	ret->green = 10;
	ret->blue = 10;
	return (ret);
}
