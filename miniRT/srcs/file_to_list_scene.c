/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/08 23:06:16 by jwadding         ###   ########.fr       */
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
			scene->shapes[i].xyz3d = normalize(current->xyz_3d);
			scene->shapes[i].rgb = current->rgb;
			scene->shapes[i].r = current->d / 2;
			scene->shapes[i].h = current->h;
			i++;
		}
		current = current->next;
	}
}

//should be called "move cam into scene"
t_elem	move_element_into_scene(t_list *current)
{
	t_elem	elem;

	elem.type = current->type;
	elem.pos.x = current->xyz.x;
	elem.pos.y = current->xyz.y;
	elem.pos.z = current->xyz.z;
	elem.xyz3d.x = current->xyz_3d.x;
	elem.xyz3d.y = current->xyz_3d.y;
	elem.xyz3d.z = current->xyz_3d.z;
	elem.focal_length = calculate_focal_len(current->fov);
	return (elem);
}
