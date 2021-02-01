#ifndef FT_SAVE_H
# define FT_SAVE_H
# define HEADERSIZE 54
# include "get_next_line.h"
int		**ft_init_buffer(int width, int height);
void		ft_free_buffer(int **del, int height);
int		ft_save_bmp(char *filename, int **target, int width, int height);
#endif
