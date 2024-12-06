/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:29:25 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/08 12:50:51 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_matrix(int **row_array, size_t row, size_t col)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!row_array || !*row_array || row <= 0 || col <= 0)
		return ;
	while (i < row)
	{
		j = 0;
		while (j < col)
			ft_printf("%d ", row_array[i][j++]);
		ft_printf("\n");
		i++;
	}
}
