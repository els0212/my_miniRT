#ifndef FT_LIBFT_H
# define FT_LIBFT_H
# include <stdlib.h>

int					ft_strncmp(const char *s1, const char *s2, int len);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_substr(const char *s, unsigned int start, size_t len);
int					ft_isspace(char c);
#endif
