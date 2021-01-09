#include "minirt.h"

t_compo			*ft_compo_init()
{
	t_compo		*ret;

	if(!(ret = (t_compo *)malloc(sizeof(t_compo))))
		return (0);
	ret->resolution = 0;
	ret->ambient = 0;
	ret->camera = 0;
	ret->light = 0;
	ret->objects = 0;
	return (ret);
}

t_object		*ft_object_init(int id)
{
	t_object	*ret;

	if (!(ret = (t_object *)malloc(sizeof(t_object))))
		return (0);
	ret->id = id;
	ret->vec = 0;
	ret->color = 0;
	ret->vec_second = 0;
	ret->vec_third = 0;
	ret->dia = 0;
	ret->height = 0;
	ret->dir = 0;
	ret->size = 0;
	ret->next = 0;
	return (ret);
}

char			**ft_parse_args(char *str)
{
	char	**chunks;
	int		len;

	if ((chunks = ft_split(str, &ft_iscomma)) == 0)
		return (0);
	len = ft_get_size(chunks);
	if (len != 3) 
	{
		free(chunks);
		return (0);
	}
	return (chunks);
}

t_vector		*ft_make_vector(char *str)
{
	t_vector	*ret;
	char		**vector;
	int			len;
	
	if (!(vector = ft_parse_args(str)) ||
			!(ret = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	if ((len = ft_get_size(vector)) != 3)
	{
		free(ret);
		return (0);
	}
	ret->x = ft_atod(vector[0]);
	ret->y = ft_atod(vector[1]);
	ret->z = ft_atod(vector[2]);
	return (ret);
}

t_color		*ft_make_color(char *str)
{
	t_color	*ret;
	char	**color;
	int		len;
	
	if (!(color = ft_parse_args(str)) ||
			!(ret = (t_color *)malloc(sizeof(t_color))))
	{
		free (color);
		return (0);
	}
	if ((len = ft_get_size(color)) != 3)
	{
		free(ret);
		return (0);
	}
	ret->red = atoi(color[0]);
	ret->green = atoi(color[1]);
	ret->blue =atoi(color[2]);
	if (ret->red < 0 || ret->green < 0 || ret->blue < 0)
	{
		free(ret);
		return (0);
	}
	free (color);
	return (ret);
}
