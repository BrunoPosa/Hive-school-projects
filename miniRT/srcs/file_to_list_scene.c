/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:34:34 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
	indexing starts from 0 for spheres, then come planes, then cylinders
*/
void	move_shapes_into_scene(t_list **l, t_scene *scene, int type)
{
	t_list	*current;
	int		i;

	current = *l;
	i = 0;
	if (type == plane)
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
