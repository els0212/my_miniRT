#include "minirt.h"

int		ft_branch(char **chunks, t_compo *compo, int size)
{
	int		ret;

	ret = 0;
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
	else
		return (-1);
	return (ret);
}

int		ft_parse(char *line, t_compo *compo)
{
	char	**chunks;
	int		size;

	if ((chunks = ft_split(line, &ft_isspace)) == 0)
		return (-1);
	if ((size = ft_get_size(chunks)))
	{
		printf("----- start -----\n");
		ft_branch(chunks, compo, size);
		printf("----- end -----\n");
	}
	ft_free(chunks, 0);
	return (0);
}
void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_close(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (0);
}

int main(int argc, char **argv)
{
	int		option;
	int		fd;
	char	*line;
	t_compo	*compo;
	t_mlx	mlx;
	t_img	img;

	compo = ft_compo_init();

	if (argc < 2 || argc > 3)
		return (-1);
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6))
		return (-1);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (-1);
	else if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
		ft_parse(line, compo);
	option = argc == 3 ? 1 : 0;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 640, 480, "hello world!");
	img.img = mlx_new_image(mlx.mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//printf("addr = %s, bpp = %d, len = %d, endian = %d\n",img.addr, img.bpp, img.line_len, img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_key_hook(mlx.win, ft_close, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
