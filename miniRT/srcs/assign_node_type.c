/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_node_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:18:55 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/08 19:22:44 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	move_past_type(t_list **l)
{
	t_list	*current;

	current = *l;
	while (current)
	{
		if (current->type == ambiant)
			current->p = current->p + 1;
		else if (current->type == camera)
			current->p = current->p + 1;
		else if (current->type == light)
			current->p = current->p + 1;
		else if (current->type == plane)
			current->p = current->p + 2;
		else if (current->type == sphere)
			current->p = current->p + 2;
		else if (current->type == cylinder)
			current->p = current->p + 2;
		current->p = skip_space(current->p);
		current = current->next;
	}
	return (E_SUCCESS);
}

int	assign_node_type(t_list **l)
{
	t_list	*current;

	current = *l;
	while (current)
	{
		if (!ft_strncmp(current->p, "A", 1))
			current->type = ambiant;
		else if (!ft_strncmp(current->p, "C", 1))
			current->type = camera;
		else if (!ft_strncmp(current->p, "L", 1))
			current->type = light;
		else if (!ft_strncmp(current->p, "pl", 2))
			current->type = plane;
		else if (!ft_strncmp(current->p, "sp", 2))
			current->type = sphere;
		else if (!ft_strncmp(current->p, "cy", 2))
			current->type = cylinder;
		else
			return (ret_error(E_WRONG_TYPE, *l));
		current = current->next;
	}
	move_past_type(l);
	return (E_SUCCESS);
}

// if current->p[0] == num, ',' 
//     return error
// if (!strcmp(current->p[0] && !strcmp(s[1] == ' '))
// A
// C
// L
// pl
// sp
// cy
// check the first letters of current->p are etc.
// update the pointer, of the s.
// update the type enum.