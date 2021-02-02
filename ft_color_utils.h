#ifndef FT_COLOR_UTILS_H
# define FT_COLOR_UTILS_H
# include "ft_struct.h"

t_color	ft_color_init(int r, int g, int b);
t_color	*ft_color_cpy(t_color *c1, t_color c2);
t_color	*ft_color_mult(t_color *c1, t_color c2);
t_color	ft_color_mult_const(t_color *c1, double ratio);
t_color	ft_color_add(t_color c1, t_color c2);
#endif
