#ifndef FT_SPLIT_H
# define FT_SPLIT_H
# include "ft_libft.h"

int					ft_iscomma(char c);
int					ft_next_idx(const char *s, int (*ft_is)(char c), int st);
int					ft_cnt_lines(const char *s, int (*ft_is)(char c));
void				ft_free(char **ret, int ret_st);
char				**ft_split(const char *s, int (*ft_is)(char c));
#endif
