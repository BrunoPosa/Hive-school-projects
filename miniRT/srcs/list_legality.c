/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_legality.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:11:44 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/21 22:57:23 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// int	only_legal_chars_n(char *s, char *legal, int n)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i] && i < n)
// 	{
// 		if (ft_strchr(legal, s[i]) == NULL)
// 		{
// 			printf("i=%d\n", i);
// 			printf("%s\n", s);
// 			return (0);
// 		}
// 		n--;
// 	}
// 	return (1);
// }

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
	Goes through list looking for illegal characters.
	Returns 1 if found an illegal char. 0 if all chars are legal.
*/
int	list_legality_check(t_list **l, char *legal)
{
	t_list	*current;

	current = *l;
	while (current)
	{	
		if (!only_legal_chars(current->p, legal))
		{
			printf("%s\n", current->p);
			printf("KO - illegal char!\n");
			return (E_ILLEGAL_CHARS_GENERAL);
		}
		current = current->next;
	}
	printf("OK - File has only legal chars.\n");
	return (0);
}
