#include "minirt.h"

t_ray	*ft_ray_init(t_vector *origin, t_vector dir)
{
	t_ray	*ret;

	ret = (t_ray *)malloc(sizeof(t_ray));
	ret->origin = ft_vec_dup(*origin);
	ret->dir = ft_vec_dup(dir);
	return (ret);
}

t_vector	ft_ray_at(t_ray *ray, double d)
{
	return (ft_vec_add(*ray->origin,
				ft_vec_product_const(*ray->dir, d)));
}

int			ft_ray_hit_sphere(t_object *sphere, t_ray *ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = ft_vec_sub(*ray->origin, *sphere->vec);
	a = ft_dot_product(*ray->dir, *ray->dir);
	b = 2.0 * ft_dot_product(oc, *ray->dir);
	c = ft_dot_product(oc, oc) - sphere->dia * sphere->dia;
	discriminant = (b * b - 4 * a * c);
	//printf("det = %f, ret = %d\n", discriminant, discriminant > 0 ? 1 : 0);
	return (discriminant > 0 ? 1 : 0);
}

t_color		*ft_ray_color(t_ray *ray, t_object *obj)
{
	t_color	*ret;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (0);
	if (ft_ray_hit_sphere(obj, ray))
		ft_color_cpy(ret, obj->color);
	else
	{
		ret->red = 10;
		ret->green = 10;
		ret->blue = 10;
	}
	return (ret);
}
