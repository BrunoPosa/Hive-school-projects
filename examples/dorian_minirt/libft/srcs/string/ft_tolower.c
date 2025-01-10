/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:04:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 18:48:43 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (0);
	return (1);
}

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	return (c);
}

void	ft_tolower2(char *c)
{
	if ('A' <= *c && *c <= 'Z')
		*c = *c + 32;
}

void	ft_strlower(char *s)
{
	if (!s)
		return ;
	while (*s)
		ft_tolower2(s++);
}
