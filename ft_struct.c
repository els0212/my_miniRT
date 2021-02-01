#include "minirt.h"

t_compo			*ft_compo_init()
{
	t_compo		*ret;

	if(!(ret = (t_compo *)malloc(sizeof(t_compo))))
		return (0);
	ret->resolution = 0;
	ret->ambient = 0;
	ret->camera = 0;
	ret->light = 0;
	ret->objects = 0;
	ret->save = 0;
	return (ret);
}

t_object		*ft_object_init(int id)
{
	t_object	*ret;

	if (!(ret = (t_object *)malloc(sizeof(t_object))))
		return (0);
	ret->id = id;
	ret->vec = 0;
	ret->color = 0;
	ret->vec_second = 0;
	ret->vec_third = 0;
	ret->dia = 0;
	ret->height = 0;
	ret->dir = 0;
	ret->size = 0;
	ret->next = 0;
	return (ret);
}

int			ft_camera_init(t_compo *compo, t_vector *vec, t_vector *dir, double angle)
{
	t_cam		*camera;
	t_vector	vup;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 || dir->z > 1 || dir->z < -1 || angle < 0 || angle > 180)
		return (ft_error("map error : a range of camera direction is wrong"));
	else if (!(camera = (t_cam *)malloc(sizeof(t_cam))))
		return (ft_error("map error : light memory allocation is failed"));
	camera->vec = vec;
	camera->dir = dir;
	camera->fov = angle * (M_PI / 180.0);
	camera->next = 0;
	vup = ft_vector_init(0, 1, 0);
	camera->v = ft_vec_dup(ft_cross_product(vup, *dir));
	camera->u = ft_vec_dup(ft_cross_product(*dir, *camera->v));
	ft_add_camera_last(&compo->camera, camera);
	return (0);
}

int			ft_light_init(t_compo *compo, t_color *color, t_vector *vec, double ratio)
{
	t_lht	*light;

	if (ratio < 0 || ratio > 1)
		return (ft_error("map error : a range of light ratio is wrong"));
	else if (!(light = (t_lht *)malloc(sizeof(t_lht))))
		return (ft_error("map error : light memory allocation is failed"));
	light->color = color;
	light->vec = vec;
	light->next = 0;
	ft_add_light_last(&compo->light, light);
	return (0);
}

int			ft_sphere_init(t_compo *compo, t_color *color, t_vector *vec, double dia)
{
	t_object	*sphere;

	if (dia <= 0)
		return (ft_error("map error : sphere diameter is less than or equals to 0"));
	else if (!(sphere = ft_object_init(SPHERE)))
		return (ft_error("map error : sphere memory allocation is failed"));
	sphere->dia = dia;
	sphere->color = color;
	sphere->vec = vec;
	ft_add_last(&compo->objects, sphere);
	return (0);
}

char			**ft_parse_args(char *str)
{
	char	**chunks;
	int		len;

	if ((chunks = ft_split(str, &ft_iscomma)) == 0)
		return (0);
	len = ft_get_size(chunks);
	if (len != 3) 
	{
		free(chunks);
		return (0);
	}
	return (chunks);
}

t_vector		ft_vector_init(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void			ft_color_init(t_color *color, int r, int g, int b)
{
	color->red = r;
	color->green = g;
	color->blue = b;
}

t_color			*ft_color_cpy(t_color *c1, t_color c2)
{
	c1->red = c2.red;
	c1->green = c2.green;
	c1->blue = c2.blue;
	return (c1);
}

t_color			*ft_color_mult(t_color *c1, t_color *c2)
{
	c1->red = fmin((c1->red * c2->red) / 255, 255);
	c1->green = fmin((c1->green * c2->green) / 255, 255);
	c1->blue = fmin((c1->blue * c2->blue) / 255, 255);
	return (c1);
}

t_color			ft_color_mult_const(t_color *c1, double ratio)
{
	t_color	ret;
	ret.red = fmin(c1->red * ratio, 255);
	ret.green = fmin(c1->green * ratio, 255);
	ret.blue = fmin(c1->blue * ratio, 255);
	return (ret);
}

t_color					ft_color_add(t_color c1, t_color c2)
{
	t_color	ret;

	ret.red = fmin(c1.red + c2.red, 255);
	ret.green = fmin(c1.green + c2.green, 255);
	ret.blue = fmin(c1.blue + c2.blue, 255);
	return (ret);
}

t_vector		*ft_make_vector(char *str)
{
	t_vector	*ret;
	char		**vector;
	int			len;
	
	if (!(vector = ft_parse_args(str)) ||
			!(ret = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	if ((len = ft_get_size(vector)) != 3)
	{
		free(ret);
		return (0);
	}
	ret->x = ft_atod(vector[0]);
	ret->y = ft_atod(vector[1]);
	ret->z = ft_atod(vector[2]);
	while (--len >= 0)
		free(vector[len]);
	free(vector);
	return (ret);
}

t_color		*ft_make_color(char *str)
{
	t_color	*ret;
	char	**color;
	int		len;
	
	if (!(color = ft_parse_args(str)) ||
			!(ret = (t_color *)malloc(sizeof(t_color))))
	{
		free (color);
		return (0);
	}
	if ((len = ft_get_size(color)) != 3)
	{
		free(ret);
		return (0);
	}
	ret->red = atoi(color[0]);
	ret->green = atoi(color[1]);
	ret->blue =atoi(color[2]);
	if (ret->red < 0 || ret->green < 0 || ret->blue < 0)
	{
		free(ret);
		return (0);
	}
	free (color);
	return (ret);
}

t_vector	ft_normalize(t_vector vec)
{
	double	size;

	size = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= size;
	vec.y /= size;
	vec.z /= size;
	return (vec);
}
