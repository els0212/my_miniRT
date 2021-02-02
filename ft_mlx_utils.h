#ifndef FT_MLX_UTILS_H
# define FT_MLX_UTILS_H
# include "mlx/mlx.h"

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_pixel
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}				t_pixel;

typedef struct	s_scene
{
	t_compo		*compo;
	t_mlx		mlx;
	t_img		img;
	int			**save;
}				t_scene;
#endif
