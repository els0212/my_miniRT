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

void	ft_render_sub(t_compo *compo, t_mlx *mlx, t_img *img, int **save)
{
	double	u;
	double	v;
	int		j;
}

void	ft_render(t_compo *compo, t_mlx *mlx, t_img *img, int **save)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_vector	dir;
	t_ray	*ray;

	i = 0;
	while (i < compo->resolution->y)
	{
		j = 0;
		while (j < compo->resolution->x)
		{
			u = (1 - 2 * ((double)i + 0.5) / (compo->resolution->y - 1))
				* tan(compo->camera->fov / 2);
			v = (2 * ((double)j + 0.5) / (compo->resolution->x - 1) - 1)
				* compo->resolution->ratio * tan(compo->camera->fov / 2);
			dir = ft_vec_add(*compo->camera->vec, ft_vec_add(
						ft_vec_add(ft_vec_mult_const(*compo->camera->u, u),
							ft_vec_mult_const(*compo->camera->v, v)), *compo->camera->dir));
			ray = ft_ray_init(compo->camera->vec, dir);
			int col = ft_mix_color(compo, ray);
			if (compo->save)
				save[i][j] = col;
			else
				my_mlx_pixel_put(img, j, i, col);
			j++;
		}
		i++;
	}
	if (compo->save)
		ft_save_bmp("save.bmp", save, img->width, img->height);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_compo	*compo;
	t_mlx	mlx;
	t_img	img;
	int		**save;

	if (ft_chk_input(argc, argv, &compo))
		return (ft_error("program arguments are not valid"));
	img.width = 1080;
	img.height = 640;
	if (img.width > compo->resolution->x)
		compo->resolution->x = img.width;
	if (img.height > compo->resolution->y)
		compo->resolution->y = img.height;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, img.width, img.height, "miniRT");
	img.img = mlx_new_image(mlx.mlx, img.width, img.height);
	img.addr = (char *)mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	mlx_hook(mlx.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_close, &mlx);
	mlx_key_hook(mlx.win, ft_rerender, &mlx);
	save = compo->save ? ft_init_buffer(img.width, img.height) : 0;
	ft_render(compo, &mlx, &img, save);
	mlx_loop(mlx.mlx);
	return (0);
}
