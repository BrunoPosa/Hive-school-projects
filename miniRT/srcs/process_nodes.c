/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:40:51 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/21 21:57:34 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// why are some functions protected and some not?

int	process_node(t_list *current)
{
	if (current->type == ambiant)
	{
		if (process_ambiant(current) != E_SUCCESS)
			return (printf(">> !!! Error: ambiant failed  !!! <<\n"));
	}
	else if (current->type == camera)
	{
		if (process_camera(current) != E_SUCCESS)
			return (printf(">> !!! Error: camera failed  !!! <<\n"));
	}
	else if (current->type == light)
	{
		if (process_light(current) != E_SUCCESS)
			return (printf(">> !!! Error: Light failed  !!! <<\n"));
	}
	else if (current->type == plane)
	{
		process_plane(current);
	}
	else if (current->type == sphere)
		process_sphere(current);
	else if (current->type == cylinder)
		process_cylinder(current);
	else
		return (printf("\n\n>> Error: has a blank line slipped through??\n\n"));
	return (E_SUCCESS);
}

int	process_nodes(t_list **l)
{
	t_list	*current;
	int		status;

	status = 0;
	current = *l;
	while (current)
	{
		status = process_node(current);
		if (status != E_SUCCESS)
			break ;
		current = current->next;
	}
	return (status);
}
