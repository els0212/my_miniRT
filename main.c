#include "minirt.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

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

void	ft_render_loop(t_scene *scene, t_cam *cam, int i)
{
	int			j;
	int			color;
	t_ray		*ray;

	j = 0;
	while (j < scene->compo->resolution->x)
	{
		ray = ft_make_ray(scene->compo->resolution, cam, i, j);
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
	int		i;
	t_cam	*now_cam;	

	i = 0;
	now_cam = ft_get_cam(scene->compo->camera, scene->cam_no);
	while (i < scene->compo->resolution->y)
		ft_render_loop(scene, now_cam, i++);
	if (scene->compo->save)
		return (ft_save_bmp("save.bmp", scene->save, scene->img.width, scene->img.height));
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->img.img, 0, 0);
	return (0);
}

int	ft_rerender(int key, t_mlx *mlx, t_scene *scene)
{
	int	new_cam_no;
	int	total_cam_no;

	total_cam_no = ft_get_cam_size(scene->compo->camera);
	if (key == CAM_UP)
	{
		new_cam_no = scene->cam_no + 1;
		scene->cam_no = (new_cam_no == total_cam_no) ? 0 : new_cam_no;
	}
	else if (key == CAM_DOWN)
	{
		new_cam_no = scene->cam_no - 1;
		scene->cam_no = (new_cam_no < 0) ? total_cam_no - 1 : new_cam_no;
	}
	else if (key == ESCAPE)
		exit(0);
	printf("cam no = %d\n", scene->cam_no);
	ft_render(scene);
	return (0);
}

int	ft_close()
{
	exit(0);
	return (0);
}

void	ft_mlx_init(t_res *res, t_img *img, t_mlx *mlx)
{
	img->width = 1080;
	img->height = 640;
	if (img->width > res->x)
		res->x = img->width;
	if (img->height > res->y)
		res->y = img->height;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, img->width, img->height, "miniRT");
	img->img = mlx_new_image(mlx->mlx, img->width, img->height);
	img->addr = (char *)mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	mlx_hook(mlx->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_close, mlx);
	mlx_key_hook(mlx->win, ft_rerender, mlx);
}

int main(int argc, char **argv)
{
	t_scene	scene;

	if (ft_chk_input(argc, argv, &scene.compo))
		return (-1);
	ft_mlx_init(scene.compo->resolution, &scene.img, &scene.mlx);
	scene.save = scene.compo->save ?
		ft_init_buffer(scene.img.width, scene.img.height) : 0;
	scene.cam_no = 0;
	if (ft_render(&scene))
		return (1);
	mlx_loop(scene.mlx.mlx);
	return (0);
}
