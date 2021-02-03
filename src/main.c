/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:43:06 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 18:18:21 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_branch(char **chunks, t_compo *compo, int size)
{
	int		ret;

	if (!ft_strncmp(chunks[0], "R", (int)ft_strlen(chunks[0])))
		ret = ft_ins_resolution(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "A", (int)ft_strlen(chunks[0])))
		ret = ft_ins_ambient(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "c", (int)ft_strlen(chunks[0])))
		ret = ft_ins_camera(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "l", (int)ft_strlen(chunks[0])))
		ret = ft_ins_light(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "sp", (int)ft_strlen(chunks[0])))
		ret = ft_ins_sphere(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "pl", (int)ft_strlen(chunks[0])))
		ret = ft_ins_plane(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "sq", (int)ft_strlen(chunks[0])))
		ret = ft_ins_square(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "cy", (int)ft_strlen(chunks[0])))
		ret = ft_ins_cylinder(chunks, compo, size);
	else if (!ft_strncmp(chunks[0], "tr", (int)ft_strlen(chunks[0])))
		ret = ft_ins_triangle(chunks, compo, size);
	else
		return (ft_error("Invalid identifier in map"));
	return (ret);
}

int		ft_parse(char *line, t_compo *compo)
{
	char	**chunks;
	int		size;

	if ((chunks = ft_split(line, &ft_isspace)) == 0)
	{
		free(line);
		return (-1);
	}
	if ((size = ft_get_chunks_size(chunks)))
	{
		if (ft_branch(chunks, compo, size))
		{
			ft_free(chunks, size);
			free(line);
			return (-1);
		}
	}
	ft_free(chunks, size);
	free(line);
	return (0);
}

int		ft_chk_input(int argc, char **argv, t_compo **compo)
{
	int		fd;
	char	*line;

	*compo = ft_compo_init();
	if (argc < 2 || argc > 3)
		return (ft_error("not valid number of arguments"));
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6))
			return (ft_error("not valid save argument"));
		else
			(*compo)->save = 1;
	}
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (ft_error("not valid map"));
	else if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (ft_error("file open failed"));
	while (get_next_line(fd, &line) > 0)
		if (ft_parse(line, *compo))
			return (-1);
	close(fd);
	return (0);
}

int		main(int argc, char **argv)
{
	t_scene	scene;

	if (ft_chk_input(argc, argv, &scene.compo))
	{
		ft_free_compo(scene.compo);
		return (-1);
	}
	scene.cam_no = 0;
	ft_mlx_init(&scene, scene.compo->resolution, &scene.img, &scene.mlx);
	if (ft_render(&scene))
		return (1);
	mlx_loop(scene.mlx.mlx);
	return (0);
}
