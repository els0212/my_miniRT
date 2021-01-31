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
	t_lht	 *curr;

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

	cnt = 1;
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
