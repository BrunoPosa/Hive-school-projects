/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_obj_man.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:04:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 13:47:19 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"

int	is_obj(char *line)
{
	ft_skip_ws(&line);
	if (ft_strncmp(line, "sp", 2) == 0
		|| ft_strncmp(line, "tm", 2) == 0
		|| ft_strncmp(line, "pl", 2) == 0
		|| ft_strncmp(line, "cy", 2) == 0
		|| ft_strncmp(line, "di", 2) == 0
		|| ft_strncmp(line, "tr", 2) == 0
		|| ft_strncmp(line, "co", 2) == 0)
		return (1);
	return (0);
}
