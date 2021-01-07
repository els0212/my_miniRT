#include "ft_miniRT.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	void *mlx;
	void *mlx_win;
	/*
	t_data img;
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, 640, 480, "hello world!");
	mlx_loop(mlx);
	*/
	int num = 1;
	printf("%d\n", num<<1);
	return (0);
}
