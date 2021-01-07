#include "ft_miniRT.h"

int		ft_strncmp(const char *s1, const char *s2, int len)
{
	int		st;

	st = 0;
	while (s1[st] && s2[st] && st < len)
	{
		if (s1[st] != s2[st])
			return ((unsigned char)s1[st] - (unsigned char)s2[st]);
		st++;
	}
	if (len <= 0 || st == len)
		return (0);
	return ((unsigned char)s1[st] - (unsigned char)s2[st]);
}

char	*ft_strrchr(const char *s, int c)
{
	int		st;
	char	*ret;

	st = 0;
	ret = 0;
	while (*(s + st))
	{
		if (*(s + st) == (char) c)
			ret = (char *)(s + st);
		st++;
	}
	if (c == '\0')
		ret = (char *)(s + ft_strlen(s));
	return (ret);
}

size_t ft_strlen(const char *s)
{
	int		st;

	st = 0;
	if (!s)
		return (st);
	while (*(s + st))
		st++;
	return (st);
}
