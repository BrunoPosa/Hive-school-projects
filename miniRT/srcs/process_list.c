/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:39:21 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 20:40:23 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	process_list(t_list **l)
{
	if (!list_legality_check(l, LEGAL_CHARS1))
		return (ret_error(E_ILLEGAL_CHARS1, *l));
	move_pointers_to_args(l);
	assign_node_type(l);
	list_legality_check(l, LEGAL_CHARS2);
	if (process_nodes(l) != E_SUCCESS)
		return (-1);
	return (E_SUCCESS);
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
