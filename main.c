#include "minirt.h"

int	ft_parse(char *line)
{
	char	**chunks;
	char	**axis;
	int		idx;
	int		sub_idx;
	
	if ((chunks = ft_split(line, &ft_isspace)) == 0)
		return (-1);
	idx = 0;
	printf("----- start -----\n");
	while (chunks[idx])
	{
		if (idx == 0)

		//printf("len = %d\n", (int)ft_strlen(chunks[idx]));
		//printf("chunks[%d] = %s\n", idx, chunks[idx]);
		/*
		if (ft_strrchr(chunks[idx], ',') &&
				(axis = ft_split(chunks[idx], &ft_iscomma)))
		{
			sub_idx = 0;
			while (axis[sub_idx])
			{
				printf("\t\tsub_axis[%d] = %s\n",sub_idx, axis[sub_idx]);
				sub_idx++;
			}
			free(axis);
		}
		*/
		idx++;
	}
	ft_free(chunks, 0);
	//printf("----- end -----\n");
	return (0);
}

int main(int argc, char **argv)
{
	char	*option;
	int		fd;
	char	*line;

	if (argc < 2 || argc > 3)
		return (-1);
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6))
		return (-1);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (-1);
	else if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
		ft_parse(line);
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
