/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/15 15:25:07 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	allocate_scene_arrays(t_scene *scene)
{
	scene->shape_count = scene->n_sphere + scene->n_plane + scene->n_cylinder;
	if (scene->shape_count > 0)
	{
		scene->shapes = ft_calloc(scene->shape_count, sizeof(t_shape));
		if (!scene->shapes)
			return (E_MALLOC);
	}
	return (E_SUCCESS);
}

//indexing starts from 0 for spheres, then come planes, then cylinders

void	move_shapes_into_scene(t_list **l, t_scene *scene, enum e_type type)
{
	t_list	*current;
	int		i;

	current = *l;
	i = 0;
	if (type == plane) // if it is a plane, then work with cyl?
		i = scene->n_sphere;
	else if (type == cylinder)
		i = scene->n_sphere + scene->n_plane;
	while (current)
	{
		if (current->type == type)
		{
			scene->shapes[i].type = type;
			scene->shapes[i].xyz = current->xyz;
			scene->shapes[i].axis = normalize(current->xyz_3d);
			scene->shapes[i].rgb = current->rgb;
			scene->shapes[i].r = current->d / 2;
			scene->shapes[i].h = current->h;
			i++;
		}
		current = current->next;
	}
}

t_cam	move_cam_into_scene(t_list *current)
{
	t_cam	cam;

	ft_memset(&cam, 0, sizeof(t_cam));
	cam.eye = current->xyz;
	cam.axis = current->xyz_3d;
	cam.foc_len = calculate_focal_len(current->fov);
	return (cam);
}
