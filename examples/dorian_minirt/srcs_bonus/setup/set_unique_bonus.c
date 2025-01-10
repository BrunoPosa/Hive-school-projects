/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unique_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:51:04 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/28 10:38:44 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	set_camera(t_scene *scene, char **line)
{
	*line += 1;
	ft_skip_ws(line);
	scene->cam.pos = get_vec3(line);
	ft_skip_ws(line);
	scene->cam.dir = get_vec3(line);
	ft_skip_ws(line);
	scene->cam.fov = get_float(line, ANGLE);
	ft_skip_ws(line);
	scene->cam.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	vec3_normalize(&scene->cam.dir);
	scene->cam.right = vec3_cross(scene->cam.dir, \
		(t_vec3){0, 1.0f, -10e-2});
	vec3_normalize(&scene->cam.right);
	scene->cam.up = vec3_cross(scene->cam.right, scene->cam.dir);
	vec3_normalize(&scene->cam.up);
	scene->cam.valid = 1;
}

static void	set_ambient(t_scene *scene, char **line)
{
	*line += 1;
	ft_skip_ws(line);
	scene->amb.ratio = get_float(line, RATIO);
	ft_skip_ws(line);
	scene->amb.colour = get_colour(line);
	scene->amb.valid = 1;
}

static void	set_lights(t_scene *scene, char **line, int index)
{
	*line += 1;
	ft_skip_ws(line);
	scene->lights[index].pos = get_vec3(line);
	ft_skip_ws(line);
	scene->lights[index].ratio = get_float(line, RATIO);
	ft_skip_ws(line);
	scene->lights[index].colour = get_colour(line);
	ft_skip_ws(line);
	scene->lights[index].valid = 1;
	scene->n_lights += 1;
}

void	set_unique(t_scene *scene, char **line)
{
	static int	flag[3];

	if (ft_strncmp("A", *line, 1) == 0 && !flag[0])
	{
		set_ambient(scene, line);
		flag[0] = 1;
	}
	else if (ft_strncmp("L", *line, 1) == 0 && flag[1] <= 6)
	{		
		set_lights(scene, line, flag[1]);
		flag[1] += 1;
	}
	else if (ft_strncmp("C", *line, 1) == 0 && !flag[2])
	{
		set_camera(scene, line);
		flag[2] = 1;
	}
	else
		ft_error(ident_err);
}
