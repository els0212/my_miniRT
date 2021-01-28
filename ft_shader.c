#include "minirt.h"

t_color	ft_specular(t_lht *now, t_ray ray)
{
	double		metalness;
	t_color		ret;
	t_color		hlight;
	t_vector	dir;
	t_vector	reflect;

	metalness = 0.1;
	ft_color_init(&hlight, 255, 255, 255);
	hlight = ft_color_mult_const(&hlight, 1 - metalness);
	ret = ft_color_add(ft_color_mult_const(ray.hit_obj->color, metalness), hlight);
	dir = ft_normalize(ft_vec_sub(*now->vec, *ray.hit_point));
	reflect = ft_vec_sub(dir, ft_vec_product_const(*ray.hit_norm, 2 * ft_dot_product(*ray.hit_norm, dir)));
	ft_color_mult_const(&ret, fmax(ft_dot_product(reflect, ft_normalize(ft_vec_sub(*ray.hit_point, *ray.origin))), 0));
	return (ret);
}

t_color	ft_get_light_color(t_lht *now, t_object *objs, t_ray ray)
{
	t_ray		*temp_ray;
	t_color		ret;
	t_color		light_color;
	t_vector	dir;
	double		cos_angle;

	ft_color_init(&ret, 0, 0, 0);
	cos_angle = 0;
	ft_color_cpy(&light_color, *now->color);
	ft_color_mult_const(&light_color, now->ratio);
	dir = ft_vec_sub(*now->vec, *ray.hit_point);//ft_normalize(ft_vec_sub(*now->vec, *ray.hit_point));
	//printf("dir.x = %f y = %f z = %f\n", dir.x, dir.y, dir.z);
	temp_ray = ft_ray_init(ft_vec_dup(ft_vec_add(*ray.hit_point, ft_vec_product_const(*ray.hit_norm, 0.1))), dir);
	if (ft_chk_intersect(objs, temp_ray) == 0 ||
			ft_get_dist(*temp_ray->hit_point, *ray.hit_point) > ft_get_dist(*now->vec, *ray.hit_point))
		cos_angle = fmax(0, ft_dot_product(*ray.hit_norm, *temp_ray->dir));
	free(temp_ray);
	ret = ft_color_mult_const(ft_color_mult(&light_color, ray.hit_obj->color), cos_angle);
	return (ret = (cos_angle != 0) ? ft_color_add(ret, ft_specular(now, ray)) : ret);
	//return (ret);
}

t_color	ft_shader(t_lht *lht, t_object *objs, t_ray ray)
{
	t_color		ret;
	t_lht		*now;
	t_color		phong_color;

	ft_color_init(&ret, 0, 0, 0);
	if (ray.ray_hit)
	{
		now = lht;
		while (now)
		{
			phong_color = ft_get_light_color(now, objs, ray);
			ret = ft_color_add(ret, phong_color);
			now = now->next;
		}
	}
	return (ret);
}
