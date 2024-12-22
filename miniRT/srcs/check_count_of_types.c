/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_count_of_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:29:02 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 17:30:29 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	check_count_of_types(t_list **l, t_scene *scene)
{
	t_list	*current;

	current = *l;
	while (current)
	{
		if (current->type == camera)
			scene->n_camera++;
		else if (current->type == sphere)
			scene->n_sphere++;
		else if (current->type == cylinder)
			scene->n_cylinder++;
		else if (current->type == plane)
			scene->n_plane++;
		else if (current->type == light)
			scene->n_light++;
		else if (current->type == ambiant)
			scene->n_ambient++;
		current = current->next;
	}
	if (scene->n_camera != 1 || scene->n_light != 1 || scene->n_ambient != 1)
		return (printf("Error\nThere must be exactly 1 camera, 1 ambiant, and 1 light in scene\n"));
	if (scene->n_sphere + scene->n_plane + scene->n_cylinder == 0)
		return (printf("Error\nThere must be at least 1 sphere, plane, or cylinder in scene\n"));
	return (E_SUCCESS);
}
