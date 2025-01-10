/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:22:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/06 14:52:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_c(char *s)
{
	int	len;

	if (!s)
		return (return_null());
	len = ft_strlen(s);
	return (write(1, s, len));
}
