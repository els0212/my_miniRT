#include "ft_ray_utils.h"

t_ray	*ft_ray_init(t_vector *origin, t_vector dir)
{
	t_ray		*ret;
	t_vector	*hit_point;

	if (!(hit_point = (t_vector *)malloc(sizeof(t_vector))) || !(ret = (t_ray *)malloc(sizeof(t_ray))))
		return (0);
	ret->origin = ft_vec_dup(*origin);
	ret->dir = ft_vec_dup(ft_normalize(ft_vec_sub(dir, *origin))); //ft_vec_dup(ft_vec_sub(dir, *origin));//
	hit_point = ft_vec_dup(ft_vector_init(RAYMAX, RAYMAX, RAYMAX));
	ret->hit_point = hit_point;
	ret->hit_obj = 0;
	ret->hit_norm = 0;
	ret->ray_hit = 0;
	return (ret);
}

t_vector	ft_ray_at(t_ray ray, double d)
{
	return (ft_vec_add(*ray.origin,
				ft_vec_mult_const(*ray.dir, d)));
}
