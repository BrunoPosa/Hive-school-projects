/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:39:21 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/21 23:03:14 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	process_list(t_list **l)
{
	int	status;

	status = list_legality_check(l, LEGAL_CHARS1);
	move_pointers_to_args(l);
	status = assign_node_type(l);
	if (status)
		return (status);
	status = list_legality_check(l, LEGAL_CHARS2);
	if (status)
		return (status);
	status = process_nodes(l);
	return (status);
}

void	move_pointers_to_args(t_list **l)
{
	t_list	*current;

	current = *l;
	while (current)
	{
		current->p = skip_space(current->p);
		current = current->next;
	}
}
