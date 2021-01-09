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
	char	**axis;
	int		idx;
	int		sub_idx;
	int		size;

	if ((chunks = ft_split(line, &ft_isspace)) == 0)
		return (-1);
	idx = 0;
	if ((size = ft_get_size(chunks)))
	{
		printf("----- start -----\n");
		ft_branch(chunks, compo, size);
		printf("----- end -----\n");
	}
	ft_free(chunks, 0);
	return (0);
}

int main(int argc, char **argv)
{
	char	*option;
	int		fd;
	char	*line;
	t_compo	*compo;

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
		//printf("%s\n", line);
	/*
	(void)argv;
	void *mlx;
	void *mlx_win;
	t_data img;
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, 640, 480, "hello world!");
	mlx_loop(mlx);
	*/
	return (0);
}
