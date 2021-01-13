#include "minirt.h"

void		ft_vec_cpy(t_vector *vec1, t_vector vec2)
{
	vec1->x = vec2.x;
	vec1->y = vec2.y;
	vec1->z = vec2.z;
}
t_vector	*ft_vec_dup(t_vector src)
{
	t_vector	*ret;

	ret = (t_vector *)malloc(sizeof(t_vector));
	ret->x = src.x;
	ret->y = src.y;
	ret->z = src.z;
	return (ret);
}

t_vector	ft_vec_add(t_vector vec1, t_vector vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}
t_vector	ft_vec_sub(t_vector vec1, t_vector vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vector	ft_vec_product_const(t_vector vec, double d)
{
	vec.x *= d;
	vec.y *= d;
	vec.z *= d;
	return (vec);
}

t_vector	ft_vec_div_const(t_vector vec, double d)
{
	vec.x /= d;
	vec.y /= d;
	vec.z /= d;
	return (vec);
}


