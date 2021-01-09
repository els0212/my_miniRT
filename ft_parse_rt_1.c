#include "minirt.h"

int		ft_ins_resolution(char **chunks, t_compo *compo, int size)
{
	t_res	*resolution;
	int		x;
	int		y;

	if (size != 3 || compo->resolution || !(resolution = (t_res *)malloc(sizeof(t_res))))
		return (-1);
	x = ft_atoi(chunks[1]);
	y = ft_atoi(chunks[2]);
	if (x <= 0 || y <= 0)
	{
		free(resolution);
		return (-1);
	}
	resolution->x = x;
	resolution->y = y;
	compo->resolution = resolution;
	printf("## processing resolution\n\
			x = %d\ny = %d\n", x, y);
	return (0);
}

int		ft_ins_ambient(char **chunks, t_compo *compo, int size)
{
	t_amb	*ambient;
	t_color	*color;

	if (size != 3 || compo->ambient || !(ambient = (t_amb *)malloc(sizeof(t_amb))))
		return (-1);
	if (!(color = ft_make_color(chunks[2])))
		return (-1);
	ambient->ratio = ft_atod(chunks[1]);
	ambient->color = color;
	compo->ambient = ambient;
	printf("## processing Ambient\n  \
	ratio = %lf\nr = %d, g = %d, b = %d\n",\
	ambient->ratio, color->red, color->green, color->blue);
	return (0);
}

int		ft_ins_camera(char **chunks, t_compo *compo, int size)
{
	t_cam		*camera;
	t_vector	*vec;
	t_vector	*dir;

	if (size != 4 || !(camera = (t_cam *)malloc(sizeof(t_cam))))
		return (-1);
	else if (!(vec = ft_make_vector(chunks[1])) ||
			!(dir = ft_make_vector(chunks[2])))
		return (-1);
	else if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1 || atoi(chunks[3]) < 0 || atoi(chunks[3]) > 180)
	{
		free(camera);
		free(vec);
		free(dir);
		return (-1);
	}
	camera->vec = vec;
	camera->dir = dir;
	camera->fov = ft_atod(chunks[3]);
	compo->camera = camera;
	printf("## processing camera\n\
	x = %lf, y = %lf, z = %lf\n\
	dir.x = %lf, dir.y = %lf, dir.z = %lf\n\
	fov = %lf\n",\
	vec->x, vec->y, vec->z,\
	dir->x, dir->y, dir->z,\
	camera->fov);
	return (0);
}

int		ft_ins_light(char **chunks, t_compo *compo, int size)
{
	t_lht		*light;
	t_vector	*vec;
	t_color		*color;

	if (size != 4)
		return (-1);
	if (!(vec = ft_make_vector(chunks[1])) ||
			!(color = ft_make_color(chunks[3])))
		return (-1);
	if (!(light = (t_lht *)malloc(sizeof(t_lht))))
		return (-1);
	light->ratio = ft_atod(chunks[2]);
	if (light->ratio < 0 || light->ratio > 1)
	{
		free(light);
		free(vec);
		free(color);
		return (-1);
	}
	light->color = color;
	light->vec = vec;
	light->next = 0;
	ft_add_light_last(&compo->light, light);
	printf("## processing Light\n  \
	ratio = %lf\nr = %d, g = %d, b = %d\n\
	coordinates x = %lf, y = %lf, z = %lf\n",\
	light->ratio, color->red, color->green, color->blue,
	compo->light->vec->x, compo->light->vec->y, compo->light->vec->z);
	return (0);
}

int		ft_ins_sphere(char **chunks, t_compo *compo, int size)
{
	t_object	*sphere;
	t_vector	*vec;
	t_color		*color;

	if (size != 4 || !(sphere = ft_object_init(SPHERE)))
		return (-1);
	if (!(vec = ft_make_vector(chunks[1])) ||
			!(color = ft_make_color(chunks[3])))
		return (-1);
	if ((sphere->dia = ft_atod(chunks[2])) <= 0)
	{
		free(vec);
		free(color);
		free(sphere);
		return (-1);
	}
	sphere->color = color;
	sphere->vec = vec;
	ft_add_last(&compo->objects, sphere);
	printf("## processing sphere\n  \
	dia = %lf\nr = %d, g = %d, b = %d\n\
	coordinates x = %lf, y = %lf, z = %lf\n",\
	sphere->dia, color->red, color->green, color->blue,
	sphere->vec->x, sphere->vec->y, sphere->vec->z);
	return (0);
}
