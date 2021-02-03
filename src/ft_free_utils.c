/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:38:19 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:38:23 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_free_utils.h"

void	ft_free_amb(t_amb *amb)
{
	free(amb->color);
	free(amb);
}

void	ft_free_cam(t_cam *cam)
{
	t_cam	*del;
	t_cam	*pred;

	del = cam;
	pred = del;
	while (del)
	{
		pred = del->next;
		free(del->vec);
		free(del->dir);
		free(del->u);
		free(del->v);
		free(del);
		del = pred;
	}
}

void	ft_free_lht(t_lht *lht)
{
	t_lht	*del;
	t_lht	*pred;

	del = lht;
	pred = del;
	while (del)
	{
		pred = del->next;
		free(del->vec);
		free(del->color);
		free(del);
		del = pred;
	}
}

void	ft_free_obj(t_object *obj)
{
	t_object	*del;
	t_object	*pred;

	del = obj;
	pred = del;
	while (del)
	{
		pred = del->next;
		free(del->vec);
		free(del->color);
		free(del->vec_second);
		free(del->vec_third);
		free(del->dir);
		free(del);
		del = pred;
	}
}

void	ft_free_compo(t_compo *compo)
{
	free(compo->resolution);
	ft_free_amb(compo->ambient);
	ft_free_cam(compo->camera);
	ft_free_lht(compo->light);
	ft_free_obj(compo->objects);
	free(compo);
}
