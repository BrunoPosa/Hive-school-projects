/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:22:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/06 13:07:24 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_bits(unsigned int n)
{
	unsigned int	val;

	val = 0;
	while (n > 1)
	{
		n >>= 1;
		val++;
	}
	return (val + 1);
}
