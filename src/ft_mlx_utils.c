/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:37:57 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:38:12 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx_utils.h"

int		ft_close(void)
{
	exit(0);
	return (0);
}

void	ft_mlx_init(t_scene *scene, t_res *res, t_img *img, t_mlx *mlx)
{
	img->width = 1080;
	img->height = 640;
	if (img->width > res->x)
		res->x = img->width;
	if (img->height > res->y)
		res->y = img->height;
	scene->save = scene->compo->save ?
		ft_init_buffer(img->width, img->height) : 0;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, img->width, img->height, "miniRT");
	img->img = mlx_new_image(mlx->mlx, img->width, img->height);
	img->addr = (char *)mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	mlx_hook(mlx->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_close, mlx);
	mlx_key_hook(mlx->win, ft_rerender, scene);
}

int		ft_rerender(int key, t_scene *scene)
{
	int	total_cam_no;

	total_cam_no = ft_get_cam_size(scene->compo->camera);
	if (key == CAM_UP)
		scene->cam_no++;
	else if (key == CAM_DOWN)
	{
		scene->cam_no--;
		if (scene->cam_no < 0)
			scene->cam_no = total_cam_no - 1;
	}
	else if (key == ESCAPE)
		exit(0);
	scene->cam_no %= total_cam_no;
	ft_render(scene);
	return (0);
}
