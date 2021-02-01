#ifndef FT_PARSE_RT_1_H
# define FT_PARSE_RT_1_H
# include "ft_struct.h"
# include "ft_error.h"
# include "ft_libft.h"
# include "ft_utils.h"
int					ft_ins_resolution(char **chunks, t_compo *compo, int size);
int					ft_ins_ambient(char **chunks, t_compo *compo, int size);
int					ft_ins_camera(char **chunks, t_compo *compo, int size);
int					ft_ins_light(char **chunks, t_compo *compo, int size);
int					ft_ins_sphere(char **chunks, t_compo *compo, int size);
#endif
