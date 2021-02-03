/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:40:06 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:44:31 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_render_loop(t_scene *scene, t_cam *cam, int i)
{
	int			j;
	int			color;
	t_ray		*ray;

	j = 0;
	while (j < scene->compo->resolution->x)
	{
		ray = ft_make_ray(scene->compo->resolution, cam, i, j);
		color = ft_mix_color(scene->compo, ray);
		ft_free_ray(ray);
		if (scene->compo->save)
			scene->save[i][j] = color;
		else
			my_mlx_pixel_put(&scene->img, j, i, color);
		j++;
	}
}

int		ft_render(t_scene *scene)
{
	int		i;
	t_cam	*now_cam;

	i = 0;
	now_cam = ft_get_cam(scene->compo->camera, scene->cam_no);
	while (i < scene->compo->resolution->y)
		ft_render_loop(scene, now_cam, i++);
	if (scene->compo->save)
	{
		return (ft_save_bmp("save.bmp", scene->save,
				scene->img.width, scene->img.height));
	}
	mlx_put_image_to_window(scene->mlx.mlx,
			scene->mlx.win, scene->img.img, 0, 0);
	return (0);
}
