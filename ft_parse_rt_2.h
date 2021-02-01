#ifndef FT_PARSE_RT_2_H
# define FT_PARSE_RT_2_H
# include "ft_struct.h"
# include "ft_error.h"
# include "ft_libft.h"
# include "ft_utils.h"
int					ft_ins_plane(char **chunks, t_compo *compo, int size);
int					ft_ins_square(char **chunks, t_compo *compo, int size);
int					ft_ins_cylinder(char **chunks, t_compo *compo, int size);
int					ft_ins_triangle(char **chunks, t_compo *compo, int size);
#endif
