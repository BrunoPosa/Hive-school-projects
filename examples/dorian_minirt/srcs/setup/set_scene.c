/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 12:00:10 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

static void	set_object(t_img *img, char *line, int id)
{
	if (!ft_isspace(line[2]))
		ft_error(ident_err);
	if (!ft_strncmp("sp", line, 2))
		create_sphere(&img->scene->objs[id].sphere, line);
	else if (!ft_strncmp("pl", line, 2))
		create_plane(&img->scene->objs[id].plane, line);
	else if (!ft_strncmp("cy", line, 2))
		create_cylinder(&img->scene->objs[id].cylinder, line);
	else
		ft_error(ident_err);
}

static void	process_line(t_img *img, char *line)
{
	static int	id;

	if (line && line[0] != '\n')
	{
		ft_skip_ws(&line);
		if (line && ft_isupper(*line))
			set_unique(img->scene, &line);
		else if (line)
		{
			set_object(img, line, id);
			check_visibility(img->scene, id);
			id++;
		}
	}
}

static void	count_calloc_objects(int fd, char *av, t_scene *scene)
{
	char	*line;
	int		count;

	line = get_next_line(fd, FALSE);
	count = 0;
	while (line)
	{
		if (!ft_empty_str(line) && is_obj(line))
			count++;
		free(line);
		line = get_next_line(fd, FALSE);
	}
	if (close(fd) < 0)
		ft_error(errno);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	scene->n_objs = count;
	scene->objs = ft_calloc(scene->n_objs, sizeof(t_object));
	if (!scene->objs)
	{
		close(fd);
		ft_error(ENOMEM);
	}
}

void	set_scene(t_img *img, t_scene *scene, char *av)
{
	int		fd;
	char	*line;

	if (ft_strncmp(av + strlen(av) - EXT_LEN, EXTENSION, EXT_LEN))
		ft_error(file_err);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	count_calloc_objects(fd, av, scene);
	if (scene->n_objs < 0)
		ft_error(content_err);
	scene->lights = ft_calloc(sizeof(t_light) * 7, 1);
	scene->n_lights = 0;
	if (!scene->objs)
		ft_error(ENOMEM);
	line = get_next_line(fd, FALSE);
	while (line != NULL)
	{
		if (!ft_empty_str(line))
			process_line(img, line);
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	close(fd);
}
