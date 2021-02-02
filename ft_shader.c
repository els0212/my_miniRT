#include "ft_shader.h"

t_color	ft_specular(t_lht *now, t_ray ray)
{
	double		metalness;
	t_color		ret;
	t_color		hlight;
	t_vector	dir;
	t_vector	reflect;

	metalness = 0.1;
	hlight = ft_color_init(255, 255, 255);
	hlight = ft_color_mult_const(&hlight, 1 - metalness);
	ret = ft_color_add(ft_color_mult_const(ray.hit_obj->color,
				metalness), hlight);
	dir = ft_normalize(ft_vec_sub(*now->vec, *ray.hit_point));
	reflect = ft_vec_sub(ft_vec_mult_const(*ray.hit_norm,
				2 * ft_dot_product(*ray.hit_norm, dir)), dir);
	ret = ft_color_mult_const(&ret, pow(fmax(ft_dot_product(reflect,
					ft_normalize(ft_vec_sub(*ray.origin,
							*ray.hit_point))), 0), 10));
	return (ret);
}

t_color	ft_get_light_color(t_lht *now, t_object *objs, t_ray ray)
{
	t_ray		*temp_ray;
	t_color		ret;
	t_color		light_color;
	t_vector	dir;
	double		diffuse;

	ret = ft_color_init(0, 0, 0);
	diffuse = 0;
	ft_color_cpy(&light_color, *now->color);
	ft_color_mult_const(&light_color, now->ratio);
	dir = ft_vec_sub(*now->vec, *ray.hit_point);
	temp_ray = ft_ray_init(ft_vec_dup(ft_vec_add(*ray.hit_point,
					ft_vec_mult_const(*ray.hit_norm, 1))), dir);
	if (ft_chk_intersect(objs, temp_ray) == 0 ||
		ft_get_dist(*temp_ray->hit_point, *ray.hit_point) >
		ft_get_dist(*now->vec, *ray.hit_point))
		diffuse = fmax(0, ft_dot_product(*ray.hit_norm, *temp_ray->dir));
	ret = ft_color_mult_const(ft_color_mult(&light_color,
				*ray.hit_obj->color), diffuse);
	free(temp_ray);
	return (ret = (diffuse != 0) ?
			ft_color_add(ret, ft_specular(now, ray)) : ret);
}

t_color	ft_shader(t_lht *lht, t_object *objs, t_ray ray)
{
	t_color		ret;
	t_lht		*now;
	t_color		phong_color;

	ret = ft_color_init(0, 0, 0);
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


int		ft_mix_color(t_compo *compo, t_ray *ray)
{
	t_color	ambient;
	t_color	shader;
	t_color	*bef;
	int		color;

	bef = ft_ray_color(ray, compo->objects);
	ambient = ft_color_mult_const(compo->ambient->color, compo->ambient->ratio);
	bef = ft_color_mult(bef, ambient);
	shader = ft_shader(compo->light, compo->objects, *ray);
	bef = ft_color_cpy(bef, ft_color_add(*bef, shader));
	color = (bef->red<<16) + (bef->green<<8) + (bef->blue);
	free(bef);
	return (color);
}
