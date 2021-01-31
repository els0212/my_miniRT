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
	t_pixel		**save;
	t_ray	*ray;

	compo = ft_compo_init();

	if (argc < 2 || argc > 3)
		return (-1);
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6))
			return (-1);
		else
			compo->save = 1;
	}
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

	// change resolution's width or height if img width or height greater than resolution's one 
	img.width = 1920;
	img.height = 1080;
	if (img.width > compo->resolution->x)
		compo->resolution->x = img.width;
	if (img.height > compo->resolution->y)
		compo->resolution->y = img.height;

	// image init
	img.img = mlx_new_image(mlx.mlx, img.width, img.height);
	img.addr = (char *)mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	// init bmp file
	save = compo->save ? ft_init_buffer(img.width, img.height) : 0;
	//rendering
	for(int i = 0 ; i <compo->resolution->y; i++)
		for(int j = 0 ; j < compo->resolution->x; j++)
		{
			double u = (1 - 2 * ((double)i + 0.5) / (compo->resolution->y - 1)) * tan(compo->camera->fov / 2);
			double v = (2 * ((double)j + 0.5) / (compo->resolution->x - 1) - 1) * compo->resolution->ratio * tan(compo->camera->fov / 2);
			t_vector dir;
			dir = ft_vec_add(*compo->camera->vec, ft_vec_add(ft_vec_add(ft_vec_product_const(*compo->camera->u, u), ft_vec_product_const(*compo->camera->v, v)), *compo->camera->dir));
			ray = ft_ray_init(compo->camera->vec, dir);
			t_color *temp_color = ft_ray_color(ray, compo->objects);
			/*
			 * ambient
			*/
			t_color ambient = ft_color_mult_const(compo->ambient->color, compo->ambient->ratio);
			temp_color = ft_color_mult(temp_color, &ambient); 
			/*
			 * diffuse + specular
			*/
			t_color shader = ft_shader(compo->light, compo->objects, *ray);
			/*
			if (ray->ray_hit && ray->hit_obj->id == PLANE)
			{
				printf("red = %d green = %d blue = %d\n", temp_color->red, temp_color->green, temp_color->blue);
				printf("shader r = %d, g = %d, b = %d\n", shader.red, shader.blue, shader.green);
			}
			printf("shader r = %d g = %d b = %d\n",shader.red, shader.green, shader.blue);
			*/
			temp_color = ft_color_cpy(temp_color, ft_color_add(*temp_color, shader));

			//printf("r = %d, g = %d, b = %d\n", temp_color->red, temp_color->blue, temp_color->green);
			//printf("amb r = %d g = %d b = %d\n",ambient.red, ambient.blue, ambient.green);
			int col = (temp_color->red<<16) + (temp_color->green<<8) + (temp_color->blue<<0);
			//int col = (temp_color->red & REDMASK) + (temp_color->green & GREENMASK) + (temp_color->blue & BLUEMASK);
			free(temp_color);
			if (compo->save)
			{
				save[i][j].red = col & REDMASK;//temp_color->red & REDMASK;
				save[i][j].green = col & GREENMASK; //temp_color->green & GREENMASK;
				save[i][j].blue = col & BLUEMASK; //temp_color->blue & BLUEMASK;
			}
			else
				my_mlx_pixel_put(&img, j, i, col);
		}
	if (compo->save)
		ft_save_bmp("hell.bmp", save, img.width, img.height);
	else
	{
		mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
		//mlx_destroy_window(&mlx.mlx, &mlx.win);
		mlx_loop(mlx.mlx);
	}
	return (0);
}
