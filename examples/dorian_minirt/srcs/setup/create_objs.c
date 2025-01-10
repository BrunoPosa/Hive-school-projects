/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:02:25 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/27 16:37:48 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_disk(t_disk *disk, char *line)
{
	disk->type = disk_obj;
	line += 3;
	disk->pos = get_vec3(&line);
	ft_skip_ws(&line);
	disk->normal = get_vec3(&line);
	vec3_normalize(&disk->normal);
	ft_skip_ws(&line);
	disk->radius = get_float(&line, REAL) / 2;
	ft_skip_ws(&line);
	disk->colour = get_colour(&line);
	check_line(&line);
}

void	create_sphere(t_sphere *sphere, char *line)
{
	sphere->type = sphere_obj;
	line += 3;
	sphere->pos = get_vec3(&line);
	ft_skip_ws(&line);
	sphere->radius = get_float(&line, REAL) / 2;
	if (sphere->radius < 0)
		ft_error(range_err);
	sphere->radius2 = pow(sphere->radius, 2.0);
	ft_skip_ws(&line);
	sphere->colour = get_colour(&line);
	check_line(&line);
}

static void	cyl_disk(t_cylinder *cylinder, int side)
{
	t_object	*disk;

	disk = malloc(sizeof(t_object));
	if (!disk)
		ft_error(ENOMEM);
	disk->disk.type = disk_obj;
	disk->disk.radius = cylinder->radius;
	disk->disk.colour = cylinder->colour;
	disk->disk.normal = cylinder->normal;
	if (side == 't')
	{
		disk->disk.pos = vec3_add(cylinder->pos,
				vec3_multf(cylinder->normal, cylinder->height / 2));
		cylinder->top = disk;
	}
	else
	{
		disk->disk.pos = vec3_sub(cylinder->pos,
				vec3_multf(cylinder->normal, cylinder->height / 2));
		cylinder->bottom = disk;
	}
}

void	create_cylinder(t_cylinder *cylinder, char *line)
{
	cylinder->type = cylinder_obj;
	line += 3;
	cylinder->pos = get_vec3(&line);
	cylinder->normal = get_vec3(&line);
	cylinder->disk_hit = 0;
	vec3_normalize(&cylinder->normal);
	ft_skip_ws(&line);
	cylinder->radius = get_float(&line, REAL) / 2;
	cylinder->radius2 = cylinder->radius * cylinder->radius;
	ft_skip_ws(&line);
	cylinder->height = get_float(&line, REAL);
	if (cylinder->height < 0 || cylinder->radius < 0)
		ft_error(range_err);
	ft_skip_ws(&line);
	cylinder->colour = get_colour(&line);
	check_line(&line);
	cyl_disk(cylinder, 't');
	cyl_disk(cylinder, 'b');
}

void	create_plane(t_plane *plane, char *line)
{
	plane->type = plane_obj;
	line += 3;
	plane->pos = get_vec3(&line);
	ft_skip_ws(&line);
	plane->normal = get_vec3(&line);
	vec3_normalize(&plane->normal);
	ft_skip_ws(&line);
	plane->colour = get_colour(&line);
	check_line(&line);
}
