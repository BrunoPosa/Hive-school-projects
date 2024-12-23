/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:53 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 04:15:46 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!
// xyz - [f], [f], [f]
// sd - [f]
// rgb - [0-255], [0-255], [0-255]


int	process_sphere(t_list *current)
{
	// these return values don't make sence - they should be the return of the other function?
	if (process_xyz(current))
		return (E_XYZ_CHARS);
	if (process_sd(current))
		return (E_SPHERE_SD);
	if (process_rgb(current))
		return (69);
	return (E_SUCCESS);
}
