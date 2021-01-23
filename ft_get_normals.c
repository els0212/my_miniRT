#include "minirt.h"

t_vector	get_sphere_normal(t_vector hit_point, t_object sphere)
{
	t_vector	ret;

	ret = ft_vec_sub(hit_point, sphere);
	ret = ft_normalize(ret);
	return (ret);
}
