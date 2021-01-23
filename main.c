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

int	ft_close()
{
	exit(0);
	return (0);
}

int	ft_key_press(int keycode)
{
	if (keycode == ESCAPE)
		exit(0);
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
	t_ray	*ray;

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
	mlx.win = mlx_new_window(mlx.mlx, compo->resolution->x, compo->resolution->y, "hello world!");
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, ft_key_press, &mlx);
	mlx_hook(mlx.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_close, &mlx);
	img.img = mlx_new_image(mlx.mlx, 640, 480);
	img.addr = (char *)mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//printf("addr = %s, bpp = %d, len = %d, endian = %d\n",img.addr, img.bpp, img.line_len, img.endian);
	/*
	for(int i = 0 ; i < 640; i++)
		for(int j = 0 ; j < 1920; j++)
			my_mlx_pixel_put(&img, i, j, 0x00FFFFFF);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_destroy_image(mlx.mlx, img.img);
	img.img = mlx_new_image(mlx.mlx, 640, 720);
	img.addr = (char *)mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	*/
	//printf("with = %f, ht = %f\n", compo->camera->ndc_width, compo->camera->ndc_height);
	//int img_w = 640;
	//int img_h = img_w / compo->resolution->ratio;
	for(int i = 0 ; i <compo->resolution->y; i++)
		for(int j = 0 ; j < compo->resolution->x; j++)
		{
			double u = (double)i / (compo->resolution->y - 1);
			double v = (double)j / (compo->resolution->x - 1);
			ray = ft_ray_init(compo->camera->vec, ft_vec_add(compo->camera->ndc_left_bottom, ft_vec_add(ft_vec_product_const(compo->camera->ndc_horizon, v), ft_vec_product_const(compo->camera->ndc_vertical, u))));
			t_color *temp_color = ft_ray_color(ray, compo->objects);
			t_color ambient = ft_color_mult_const(compo->ambient->color, compo->ambient->ratio);
			temp_color = ft_color_mult(temp_color, &ambient); 
			//printf("r = %d, g = %d, b = %d\n", temp_color->red, temp_color->blue, temp_color->green);
			//printf("amb r = %d g = %d b = %d\n",ambient.red, ambient.blue, ambient.green);
			int col = (temp_color->red<<16) + (temp_color->green<<8) + (temp_color->blue<<0);
				free(temp_color);
			my_mlx_pixel_put(&img, j, i, col);
		}
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	//mlx_destroy_window(&mlx.mlx, &mlx.win);
	mlx_loop(mlx.mlx);
	return (0);
}
