/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:38:30 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:38:42 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		ft_get_cam_size(t_cam *list)
{
	int		cnt;
	t_cam	*curr;

	cnt = 0;
	curr = list;
	while (curr)
	{
		cnt++;
		curr = curr->next;
	}
	return (cnt);
}

t_cam	*ft_get_cam(t_cam *list, int i)
{
	int		cnt;
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
