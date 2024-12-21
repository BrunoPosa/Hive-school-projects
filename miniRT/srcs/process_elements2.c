/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:53 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/21 21:53:29 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!
// xyz - [f], [f], [f]
// sd - [f]
// rgb - [0-255], [0-255], [0-255]

int	process_sphere(t_list *current)
{
	if (process_xyz(current) != E_SUCCESS)
		return (ret_error(E_XYZ_CHARS, current));
	if (process_sd(current) != E_SUCCESS)
		return (ret_error(E_SPHERE_SD, current));
	if (process_rgb(current) != E_SUCCESS)
		return (ret_error(E_RGB_CHARS, current));
	return (E_SUCCESS);
}
