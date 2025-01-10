/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:56:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 18:49:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (0);
	return (1);
}

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
	return (c);
}

void	ft_toupper2(char *c)
{
	if ('a' <= *c && *c <= 'z')
		*c = *c - 32;
}

void	ft_strupper(char *s)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i++])
		ft_toupper2(&s[i]);
}
