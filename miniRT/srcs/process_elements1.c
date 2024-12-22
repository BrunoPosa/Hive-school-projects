/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:38 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 21:58:40 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

	// alr - 0.0 - 1.0
	// rgb - [0-255], [0-255], [0-255]
int	process_ambiant(t_list *current)
{
	int	status;

	status = E_SUCCESS;
	status = process_ratio(current);
	if (status)
		return (status);
	status = process_rgb(current);
	if (status)
		return (status);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (E_EXTRA_CHARS);
	return (status);
}

	// xyz - [f], [f], [f]
	// xyz_3d - [-1,1], [-1,1], [-1,1]
	// fov - [0-180]
int	process_camera(t_list *current)
{
	int	status;

	status = E_SUCCESS;
	status = process_xyz(current);
	if (status)
		return (status);
	status = process_xyz_3d(current);
	if (status)
		return (status);
	status = process_fov(current);
	if (status)
		return (status);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (E_EXTRA_CHARS);
	return (status);
}
	// xyz - [f], [f], [f]
	// xyz_3d - [-1,1], [-1,1], [-1,1]
	// cd - [f]
	// ch - [f]
	// rgb - [0-255], [0-255], [0-255]

int	process_cylinder(t_list *current)
{
	int	status;

	status = E_SUCCESS;
	status = process_xyz(current);
	if (status)
		return (status);
	status = process_xyz_3d(current);
	if (status)
		return (status);
	status = process_cd(current);
	if (status)
		return (status);
	status = process_ch(current);
	if (status)
		return (status);
	status = process_rgb(current);
	if (status)
		return (status);
	return (status);
}
	// xyz - [f], [f], [f]
	// xyz_3d - [-1,1], [-1,1], [-1,1]
	// rgb - [0-255], [0-255], [0-255]

int	process_plane(t_list *current)
{
	int	status;
	
	status = E_SUCCESS;
	status = process_xyz(current);
	if (!status)
		status = process_xyz_3d(current);
	if (!status)
		status = process_rgb(current);
	return (status);
}

	// xyz - [f], [f], [f]
	// lbr - [0-1]
	// rgb - [0-255], [0-255], [0-255]
int	process_light(t_list *current)
{
	int	status;

	status = E_SUCCESS;
	status = process_xyz(current);
	if (status)
		return (status);
	status = process_ratio(current);
	if (status)
		return (status);
	status = process_rgb(current);
	if (status)
		return (status);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (E_EXTRA_CHARS);
	return (status);
}
