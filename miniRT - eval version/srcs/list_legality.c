/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_legality.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:11:44 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:39:50 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	only_legal_chars(char *s, char *legal)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_strchr(legal, s[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

/*
	Goes through list looking and sends each string to be checked
	for  illegal characters.
	Returns E_ILLEGAL_CHARS_GENERAL if found an illegal char.
	E_SUCCESS if all chars are legal.
*/
int	list_legality_check(t_list **l, char *legal)
{
	t_list	*current;

	current = *l;
	while (current)
	{	
		if (!only_legal_chars(current->p, legal))
			return (E_ILLEGAL_CHARS_GENERAL);
		current = current->next;
	}
	return (E_SUCCESS);
}
