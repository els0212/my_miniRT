/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:59:43 by hyi               #+#    #+#             */
/*   Updated: 2021/01/07 22:27:53 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_miniRT.h"

int		ft_iscomma(char c)
{
	if (c == ',')
		return (1);
	return (0);
}

int		ft_next_idx(const char *s, int (*ft_is)(char c), int st)
{
	while (s[st] && ft_is(s[st]) == 0)
		st++;
	return (st);
}

int		ft_cnt_lines(const char *s, int (*ft_is)(char c))
{
	int	st;
	int	cnt;

	st = 0;
	cnt = 0;
	while (s[st] && ft_is(s[st]))
		st++;
	while (s[st])
	{
		st = ft_next_idx(s,ft_is, st);
		cnt++;
		while (s[st] && ft_is(s[st]))
			st++;
	}
	return (cnt);
}

void	ft_free(char **ret, int ret_st)
{
	int	st;

	st = 0;
	while (st < ret_st)
		free(ret[st]);
	free(ret);
}

char	**ft_split(const char *s, int (*ft_is)(char c))
{
	char	**ret;
	int		ret_st;
	int		st;

	if (!s)
		return (0);
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_cnt_lines(s, ft_is) + 1))))
		return (0);
	ret_st = 0;
	st = 0;
	while (s[st] && ft_is(s[st]))
		st++;
	while (s[st] && ret_st < ft_cnt_lines(s, ft_is))
	{
		if (!(ret[ret_st++] = ft_substr(s, st, ft_next_idx(s, ft_is, st) - st)))
		{
			ft_free(ret, ret_st);
			return (0);
		}
		st = ft_next_idx(s, ft_is, st);
		while (s[st] && ft_is(s[st]))
			st++;
	}
	ret[ret_st] = 0;
	return (ret);
}
