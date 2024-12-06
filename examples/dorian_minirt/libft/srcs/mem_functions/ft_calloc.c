/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:56:42 by djagusch          #+#    #+#             */
/*   Updated: 2022/10/28 14:56:42 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_arr;

	if (size == 0 || nmemb == 0)
		return (ft_calloc(1, 1));
	if ((nmemb > 0 && (nmemb * size) / nmemb != size)
		|| (size > 0 && (nmemb * size) / size != nmemb))
		return (NULL);
	mem_arr = (void *)malloc(sizeof(*mem_arr) * (nmemb * size));
	if (!mem_arr)
		return (NULL);
	ft_bzero(mem_arr, nmemb * size);
	return (mem_arr);
}
