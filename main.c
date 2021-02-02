#include "minirt.h"

int		ft_branch(char **chunks, t_compo *compo, int size)
{
	int		ret;

	ret = -1;
	if (!ft_strncmp(chunks[0], "R", (int)ft_strlen(chunks[0])))
		ret = ft_ins_resolution(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "A", (int)ft_strlen(chunks[0])))
		ret = ft_ins_ambient(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "c", (int)ft_strlen(chunks[0])))
		ret = ft_ins_camera(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "l", (int)ft_strlen(chunks[0])))
		ret = ft_ins_light(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "sp", (int)ft_strlen(chunks[0])))
		ret = ft_ins_sphere(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "pl", (int)ft_strlen(chunks[0])))
		ret = ft_ins_plane(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "sq", (int)ft_strlen(chunks[0])))
		ret = ft_ins_square(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "cy", (int)ft_strlen(chunks[0])))
		ret = ft_ins_cylinder(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "tr", (int)ft_strlen(chunks[0])))
		ret = ft_ins_triangle(chunks, compo, size);
	return (ret);
}

int		ft_parse(char *line, t_compo *compo)
{
	char	**chunks;
	int		size;

	if ((chunks = ft_split(line, &ft_isspace)) == 0)
		return (-1);
	if ((size = ft_get_chunks_size(chunks)))
	{
		if (ft_branch(chunks, compo, size))
		{
			ft_free_compo(compo);
			return (-1);
		}
		ft_free(chunks, size);
	}
	return (0);
}

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_close()
{
	exit(0);
	return (0);
}

int	ft_chk_input(int argc, char **argv, t_compo **compo)
{
	int		fd;
	char	*line;

	*compo = ft_compo_init();
	if (argc < 2 || argc > 3)
		return (-1);
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6))
			return (-1);
		else
			(*compo)->save = 1;
	}
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (-1);
	else if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
		if (ft_parse(line, *compo))
			return (-1);
	return (0);
}

int	ft_rerender(int key, t_mlx *mlx)
{
	if (key == CAM_UP)
		;
	else if (key == CAM_DOWN)
		;
	else if (key == ESCAPE)
		exit(0);
	(void *)mlx;
	return (0);
}

void	ft_render_loop(t_scene *scene, int i)
{
	int			j;
	int			color;
	t_ray		*ray;

	j = 0;
	while (j < scene->compo->resolution->x)
	{
		ray = ft_make_ray(scene->compo->resolution, scene->compo->camera, i, j);
		color = ft_mix_color(scene->compo, ray);
		ft_free_ray(ray);
		if (scene->compo->save)
			scene->save[i][j] = color;
		else
			my_mlx_pixel_put(&scene->img, j, i, color);
		j++;
	}
}

int		ft_render(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < scene->compo->resolution->y)
		ft_render_loop(scene, i++);
	if (scene->compo->save)
		return (ft_save_bmp("save.bmp", scene->save, scene->img.width, scene->img.height));
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->img.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_scene	scene;

	if (ft_chk_input(argc, argv, &scene.compo))
		return (ft_error("program arguments are not valid"));
	scene.img.width = 1080;
	scene.img.height = 640;
	if (scene.img.width > scene.compo->resolution->x)
		scene.compo->resolution->x = scene.img.width;
	if (scene.img.height > scene.compo->resolution->y)
		scene.compo->resolution->y = scene.img.height;
	scene.mlx.mlx = mlx_init();
	scene.mlx.win = mlx_new_window(scene.mlx.mlx, scene.img.width,
			scene.img.height, "miniRT");
	scene.img.img = mlx_new_image(scene.mlx.mlx, scene.img.width,
			scene.img.height);
	scene.img.addr = (char *)mlx_get_data_addr(scene.img.img, &scene.img.bpp,
			&scene.img.line_len, &scene.img.endian);
	mlx_hook(scene.mlx.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_close, &scene.mlx);
	mlx_key_hook(scene.mlx.win, ft_rerender, &scene.mlx);
	scene.save = scene.compo->save ?
		ft_init_buffer(scene.img.width, scene.img.height) : 0;
	if (ft_render(&scene))
		return (1);
	mlx_loop(scene.mlx.mlx);
	return (0);
}
