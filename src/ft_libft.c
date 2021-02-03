/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:38:47 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:38:48 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"

int			ft_strncmp(const char *s1, const char *s2, int len)
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

char		*ft_strrchr(const char *s, int c)
{
	int		st;
	char	*ret;

	st = 0;
	ret = 0;
	while (*(s + st))
	{
		if (*(s + st) == (char)c)
			ret = (char *)(s + st);
		st++;
	}
	if (c == '\0')
		ret = (char *)(s + ft_strlen(s));
	return (ret);
}

size_t		ft_strlen(const char *s)
{
	int		st;

	st = 0;
	if (!s)
		return (st);
	while (*(s + st))
		st++;
	return (st);
}

char		*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	ed;
	size_t	st;

	if (!s)
		return (0);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	st = 0;
	if (ft_strlen(s) >= (size_t)start)
	{
		ed = start + len;
		while (start < ed)
			ret[st++] = s[start++];
	}
	ret[st] = '\0';
	return (ret);
}

int			ft_isspace(char c)
{
	if (c == 0x20 || (c >= 0x09 && c <= 0x0D))
		return (1);
	return (0);
}
