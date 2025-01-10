/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:04:41 by djagusch          #+#    #+#             */
/*   Updated: 2022/10/27 19:04:41 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		i;

	if (!lst)
		return (0);
	tmp = lst;
	i = 1;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
