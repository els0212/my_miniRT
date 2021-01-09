#include "minirt.h"

int		ft_ins_resolution(char **chunks, t_compo *compo, int size)
{
	t_res	*resolution;
	int		x;
	int		y;

	if (size != 3)
		return (-1);
	x = ft_atoi(chunks[1]);
	y = ft_atoi(chunks[2]);
	if (x <= 0 || y <= 0)
		return (-1);
	if (!(resolution = (t_res *)malloc(sizeof(t_res))))
		return (-1);
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

	if (size != 3)
		return (-1);
	if (!(color = ft_make_color(chunks[2])))
		return (-1);
	if (!color || !(ambient = (t_amb *)malloc(sizeof(t_amb))))
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

	if (size != 4)
		return (-1);
	else if (!(vec = ft_make_vector(chunks[1])) ||
			!(dir = ft_make_vector(chunks[2])))
		return (-1);
	else if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
		return (-1);
	if (atoi(chunks[3]) < 0 || atoi(chunks[3]) > 180)
		return (-1);
	if (!(camera = (t_cam *)malloc(sizeof(t_cam))))
		return (-1);
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
		;
	else if (!ft_strncmp(chunks[0], "sp", (int)ft_strlen(chunks[0])))
		;
	else if (!ft_strncmp(chunks[0], "pl", (int)ft_strlen(chunks[0])))
		;
	else if (!ft_strncmp(chunks[0], "cy", (int)ft_strlen(chunks[0])))
		;
	else if (!ft_strncmp(chunks[0], "tr", (int)ft_strlen(chunks[0])))
		;
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
