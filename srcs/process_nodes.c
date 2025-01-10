/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:40:51 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:45:09 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	process_node(t_list *current)
{
	if (current->type == ambiant)
		return (process_ambiant(current));
	else if (current->type == camera)
		return (process_camera(current));
	else if (current->type == light)
		return (process_light(current));
	else if (current->type == plane)
		return (process_plane(current));
	else if (current->type == sphere)
		return (process_sphere(current));
	else if (current->type == cylinder)
		return (process_cylinder(current));
	else
		return (E_ERROR);
}

int	process_nodes(t_list **l)
{
	t_list	*current;
	int		status;

	current = *l;
	status = 0;
	while (current)
	{
		status = process_node(current);
		if (status)
			break ;
		current = current->next;
	}
	return (status);
}
