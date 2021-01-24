#include "minirt.h"

t_color	ft_get_light_color(t_lht *now, t_object *objs, t_ray ray)
{
	t_ray		*temp_ray;
	t_color		ret;
	t_color		light_color;
	t_vector	dir;
	double		diffused;

	ft_color_init(&ret, 0, 0, 0);
	ft_color_cpy(&light_color, *now->color);
	dir = ft_vec_sub(*now->vec, *ray.hit_point);//ft_normalize(ft_vec_sub(*now->vec, *ray.hit_point));
	//printf("dir.x = %f y = %f z = %f\n", dir.x, dir.y, dir.z);
	temp_ray = ft_ray_init(ray.hit_point, dir);
	if (ft_chk_intersect(objs, temp_ray) == 0 ||
			ft_get_dist(*temp_ray->hit_point, *ray.hit_point) > ft_get_dist(*now->vec, *ray.hit_point))
	{
		diffused = fmax(0, ft_dot_product(*ray.hit_norm, *temp_ray->dir));
		ft_color_mult_const(&light_color, now->ratio);
		ret = ft_color_mult_const(ft_color_mult(&light_color, ray.hit_obj->color), diffused);
	}
	free(temp_ray);
	return (ret);
}

t_color	ft_shader(t_lht *lht, t_object *objs, t_ray ray)
{
	t_color		ret;
	t_lht		*now;
	t_color		light_color;

	ft_color_init(&ret, 0, 0, 0);
	now = lht;
	while (now)
	{
		light_color = ft_get_light_color(now, objs, ray);
		ret = ft_color_add(ret, light_color);
		now = now->next;
	}
	return (ret);
}
