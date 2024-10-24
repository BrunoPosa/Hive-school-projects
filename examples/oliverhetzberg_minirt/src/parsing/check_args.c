/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:00:22 by ohertzbe          #+#    #+#             */
/*   Updated: 2024/08/27 15:03:58 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		error_msg("number of arguments is not valid!\n",
			"Usage: ./miniRT <scene_file.rt>\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strchr(argv[1], '.') == NULL
		|| ft_strcmp(ft_strchr(argv[1], '.'), ".rt") != 0)
	{
		error_msg("argument is not correct!\n",
			"Usage: ./miniRT <scene_file.rt>\n");
		exit(EXIT_FAILURE);
	}
}
