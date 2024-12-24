/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:06:40 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/24 21:25:58 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_list	*ft_lstnew(void *s)
{
	t_list	*new_node;

	new_node = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->s = s;
	new_node->next = NULL;
	return (new_node);
}
