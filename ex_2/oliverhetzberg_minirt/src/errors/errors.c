/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:26:16 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 18:54:32 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/errors.h"

void	error_msg(char *c, char *str)
{
	write(2, "Error\n", 7);
	if (c)
		write(2, c, ft_strlen(c));
	if (str)
		write(2, str, ft_strlen(str));
	if (!c && !str)
		write(2, "unknown error!\n", 15);
}

void	malloc_error(void)
{
	ft_putstr_fd("Memory allocation failed.\n", 2);
	exit(EXIT_FAILURE);
}
