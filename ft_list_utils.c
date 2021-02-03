#include "ft_list_utils.h"

void	ft_add_last(t_object **list, t_object *obj)
{
	t_object	*curr;

	if (!*list)
		*list = obj;
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = obj;
	}
}

void	ft_add_light_last(t_lht **list, t_lht *obj)
{
	t_lht	*curr;

	if (!*list)
		*list = obj;
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = obj;
	}
}

void	ft_add_camera_last(t_cam **list, t_cam *obj)
{
	t_cam	*curr;
	int		cnt;

	cnt = 0;
	if (!*list)
		*list = obj;
	else
	{
		curr = *list;
		cnt++;
		while (curr->next)
		{
			curr = curr->next;
			cnt++;
		}
		curr->next = obj;
	}
	obj->order = cnt;
}

t_cam	*ft_get_cam(t_cam *list, int i)
{
	int	cnt;
	t_cam	*curr;

	cnt = 0;
	if (!list || i < 0)
		return (0);
	curr = list;
	while (curr)
	{
		if (curr->order == i)
			return (curr);
		curr = curr->next;
	}
	return (0);
}
