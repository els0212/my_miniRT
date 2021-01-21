#include "minirt.h"

int		ft_get_size(char **chunks)
{
	int	cnt;

	cnt = 0;
	while (chunks[cnt])
		cnt++;
	return (cnt);
}

int		ft_get_sign(const char *nptr, int *sign)
{
	int	ret;
	int	st;

	ret = 0;
	st = 0;
	*sign = 1;
	if (!nptr[st])
		return (-1);
	if (nptr[st] == '-')
		*sign = -1;
	if (*sign == -1 || nptr[st] == '+')
		st++;
	while (nptr[st] && nptr[st] >= '0' && nptr[st] <= '9')
		st++;
	return (st);
}

int		ft_atoi(const char *nptr)
{
	int		st;
	int		ret;
	int		sign;
	int		mul;

	if ((st = ft_get_sign(nptr, &sign)) < 0)
		return (0);
	mul = 1;
	ret = 0;
	while (nptr[--st] && nptr[st] >= '0' && nptr[st] <= '9')
	{
		if (st < 0)
			break ;
		ret += (nptr[st] - '0') * mul;
		mul *= 10;
	}
	return (ret * sign);
}

double	ft_atod(const char *nptr)
{
	int		st;
	int		pt_st;
	int		sign;
	double	ret;
	double	mul;

	if ((st = ft_get_sign(nptr, &sign)) < 0)
		return (0);
	mul = 0.1;
	pt_st = st;
	if (nptr[pt_st] == '.')
		pt_st++;
	ret = ft_atoi(nptr) * sign;
	//printf("bef ret = %f, pt_st = %d, nptr[pt_st] = %c\n", ret, pt_st, nptr[pt_st]);
	while (nptr[pt_st] && nptr[pt_st] >= '0' && nptr[pt_st] <= '9')
	{
		ret += ((nptr[pt_st] - '0') * mul);
		mul *= 0.1;
		pt_st++;
	}
	//printf("final ret = %f\n", ret * sign);
	return (ret * sign);
}
