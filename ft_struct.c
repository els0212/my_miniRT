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

int			ft_plane_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir)
{
	t_object	*plane;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
		return (ft_error("map error : a range of plane direction is wrong"));
	else if (!(plane = ft_object_init(PLANE)))
		return (ft_error("map error : plane memory allocation is failed"));
	plane->color = color;
	plane->dir = dir;
	plane->vec = vec;
	ft_add_last(&compo->objects, plane);
	return (0);
}

t_object		*ft_square_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir)
{
	t_object	*square;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		ft_error("map error : a range of square direction is wrong");
		return (0);
	}
	else if (!(square = ft_object_init(SQUARE)))
	{
		ft_error("map error : square memory allocation is failed");
		return (0);
	}
	square->color = color;
	square->dir = dir;
	square->vec = vec;
	ft_add_last(&compo->objects, square);
	return (square);
}

t_object		*ft_cylinder_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir)
{
	t_object	*cylinder;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		ft_error("map error : a range of cylinder direction is wrong");
		return (0);
	}
	else if (!(cylinder = ft_object_init(CYLINDER)))
	{
		ft_error("map error : cylinder memory allocation is failed");
		return (0);
	}
	cylinder->color = color;
	cylinder->dir = dir;
	cylinder->vec = vec;
	ft_add_last(&compo->objects, cylinder);
	return (cylinder);
}

int			ft_triangle_init(t_compo *compo, t_color *color, char **chunks)
{
	t_object	*triangle;
	t_vector	*vec[3];
	int			st;

	st = 0;
	if (!(triangle = ft_object_init(TRIANGLE)))
		return (ft_error("map error : triangle memory allocation is failed"));
	while (st < 3)
	{
		if (!(vec[st] = ft_chunks_to_vec(chunks[st + 1])))
		{
			while (st >= 0)
				free(vec[st]);
			free(triangle);
			return (ft_error("map error : triangle coordinate is wrong"));
		}
		st++;
	}
	triangle->color = color;
	triangle->vec = vec[0];
	triangle->vec_second = vec[1];
	triangle->vec_third = vec[2];
	ft_add_last(&compo->objects, triangle);
	return (0);
}

char			**ft_parse_args(char *str)
{
	char	**chunks;
	int		len;

	if ((chunks = ft_split(str, &ft_iscomma)) == 0)
		return (0);
	len = ft_get_chunks_size(chunks);
	if (len != 3) 
	{
		ft_free(chunks, len);
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

t_vector		*ft_chunks_to_vec(char *str)
{
	t_vector	*vec;
	char		**chunks;
	
	if (!(chunks = ft_parse_args(str)) ||
			!(vec = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	vec->x = ft_atod(chunks[0]);
	vec->y = ft_atod(chunks[1]);
	vec->z = ft_atod(chunks[2]);
	ft_free(chunks, ft_get_chunks_size(chunks));
	return (vec);
}

t_color		*ft_chunks_to_color(char *str)
{
	t_color	*color;
	char	**chunks;
	
	if (!(chunks = ft_parse_args(str)) ||
			!(color = (t_color *)malloc(sizeof(t_color))))
		return (0);
	color->red = atoi(chunks[0]);
	color->green = atoi(chunks[1]);
	color->blue =atoi(chunks[2]);
	if (color->red < 0 || color->green < 0 || color->blue < 0)
	{
		free(color);
		ft_free(chunks, ft_get_chunks_size(chunks));
		return (0);
	}
	ft_free (chunks, ft_get_chunks_size(chunks));
	return (color);
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
