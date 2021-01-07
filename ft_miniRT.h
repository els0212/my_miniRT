#ifndef FT_MINIRT_H
# define FT_MINIRT_H
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "mlx/mlx.h"
#include <stdio.h>

/*
** get_next_line_utils.c
*/
int		ft_memset(char **line, size_t size);
int		ft_get_new_line_idx(char *buf);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_resize_and_copy(char **line, char *buf, int st, int ed);
char	*ft_strdup(char *str);
/*
** get_next_line.c
*/
int		ft_get_len(char *str);
int		ft_while_loop(char **line, char *buf, char **buf_ref);
int		ft_proc_buf_ref(char **line, char **buf_ref);
int		get_next_line(int fd, char **line);
#endif
