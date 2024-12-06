/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:41:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/21 13:54:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_d(t_list **head)
{
	t_list	*cur;

	if (!head && !*head)
		return ;
	cur = *head;
	while (cur)
	{
		ft_printf("%d->", cur->content);
	}
	ft_printf("(null)");
}

void	ft_lstprint_c(t_list **head)
{
	t_list	*cur;

	if (!head && !*head)
		return ;
	cur = *head;
	while (cur)
	{
		ft_printf("%c->", cur->content);
	}
	ft_printf("(null)");
}

void	ft_lstprint_s(t_list **head)
{
	t_list	*cur;

	if (!head && !*head)
		return ;
	cur = *head;
	while (cur)
	{
		ft_printf("%s->", cur->content);
	}
	ft_printf("(null)");
}

void	ft_lstprint_x(t_list **head)
{
	t_list	*cur;

	if (!head && !*head)
		return ;
	cur = *head;
	while (cur)
	{
		ft_printf("%x->", cur->content);
	}
	ft_printf("(null)");
}

void	ft_lstprint_p(t_list **head)
{
	t_list	*cur;

	if (!head && !*head)
		return ;
	cur = *head;
	while (cur)
	{
		ft_printf("%p->", cur->content);
	}
	ft_printf("(null)");
}
