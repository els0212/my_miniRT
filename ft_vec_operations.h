#ifndef FT_VEC_OPERATIONS_H
# define FT_VEC_OPERATIONS_H
# include "ft_struct.h"

t_vector			*ft_vec_dup(t_vector src);
t_vector			ft_vec_add(t_vector vec1, t_vector vec2);
t_vector			ft_vec_sub(t_vector vec1, t_vector vec2);
t_vector			ft_vec_mult_const(t_vector vec, double d);
t_vector			ft_vec_div_const(t_vector vec, double d);
#endif
