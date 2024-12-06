/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:22:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/06 14:52:49 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_c2(char *s, int fd)
{
	int	len;

	if (!s)
		return (return_null2(fd));
	len = ft_strlen(s);
	return (write(fd, s, len));
}
