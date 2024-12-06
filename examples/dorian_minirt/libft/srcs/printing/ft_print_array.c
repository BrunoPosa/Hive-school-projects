/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:29:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/22 16:25:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(char **str, int fd)
{
	int	i;

	i = -1;
	if (!str || fd < 0)
		return ;
	while (str[++i])
		ft_putendl_fd(str[i], fd);
}

void	ft_print_intarr(int *arr, int size, int fd)
{
	int	i;

	i = 0;
	if (!arr || !size || fd < 0)
		return ;
	ft_printf_fd(fd, "[ ");
	while (i < size - 1)
		ft_printf_fd(fd, "%d ; ", arr[i++]);
	ft_printf_fd(fd, "%d ]\n", arr[i]);
}
