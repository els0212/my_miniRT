#include "ft_parse_utils_2.h"

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

