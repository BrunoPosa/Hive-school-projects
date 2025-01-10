/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:39:21 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:43:57 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	move_pointers_to_args(t_list **l)
{
	t_list	*current;

	current = *l;
	while (current)
	{
		current->p = skip_space(current->p);
		current = current->next;
	}
}

int	process_list(t_list **l)
{
	if (list_legality_check(l, LEGAL_CHARS1))
		return (E_ILLEGAL_CHARS1);
	move_pointers_to_args(l);
	if (assign_node_type(l))
		return (E_WRONG_TYPE);
	if (list_legality_check(l, LEGAL_CHARS2))
		return (E_ILLEGAL_CHARS2);
	return (process_nodes(l));
}
