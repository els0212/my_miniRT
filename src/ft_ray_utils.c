/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:40:55 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:40:56 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ray_utils.h"

t_ray		*ft_ray_init(t_vector *origin, t_vector dir)
{
	t_ray		*ret;
	t_vector	*hit_point;

	if (!(hit_point = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	else if (!(ret = (t_ray *)malloc(sizeof(t_ray))))
	{
		free(hit_point);
		return (0);
	}
	ret->origin = ft_vec_dup(*origin);
	ret->dir = ft_vec_dup(ft_normalize(ft_vec_sub(dir, *origin)));
	hit_point = ft_vec_dup(ft_vector_init(RAYMAX, RAYMAX, RAYMAX));
	ret->hit_point = hit_point;
	ret->hit_obj = 0;
	ret->hit_norm = 0;
	ret->ray_hit = 0;
	return (ret);
}

t_vector	ft_ray_at(t_ray ray, double d)
{
	return (ft_vec_add(*ray.origin,
				ft_vec_mult_const(*ray.dir, d)));
}

int			ft_ray_change_hit(t_ray *ray, int t, t_object *hit_obj)
{
	t_vector	now;

	now = ft_vec_add(*ray->origin, ft_vec_mult_const(*ray->dir, t));
	if (ft_get_dist(*ray->origin, *ray->hit_point) >
			ft_get_dist(*ray->origin, now))
	{
		free(ray->hit_point);
		ray->hit_point = ft_vec_dup(now);
		ray->hit_obj = hit_obj;
		ray->ray_hit = 1;
		return (1);
	}
	return (0);
}

t_ray		*ft_make_ray(t_res *res, t_cam *cam, int i, int j)
{
	double		u;
	double		v;
	t_vector	dir;
	t_ray		*ray;

	u = (1 - 2 * ((double)i + 0.5) / (res->y - 1))
		* tan(cam->fov / 2);
	v = (2 * ((double)j + 0.5) / (res->x - 1) - 1)
		* res->ratio * tan(cam->fov / 2);
	dir = ft_vec_add(*cam->vec, ft_vec_add(
			ft_vec_add(ft_vec_mult_const(*cam->u, u),
					ft_vec_mult_const(*cam->v, v)), *cam->dir));
	ray = ft_ray_init(cam->vec, dir);
	return (ray);
}

void		ft_free_ray(t_ray *ray)
{
	free(ray->origin);
	free(ray->dir);
	free(ray->hit_point);
	free(ray->hit_norm);
	free(ray);
	ray = 0;
}
