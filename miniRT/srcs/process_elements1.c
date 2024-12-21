/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:38 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/21 21:50:25 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

	// alr - 0.0 - 1.0
		// rgb - [0-255], [0-255], [0-255]
int	process_ambiant(t_list *current)
{
	int	status;

	status = process_alr(current);
	if (status != E_SUCCESS)
		return (status);
	status = process_rgb(current);
	if (status != E_SUCCESS)
		return (status);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (ret_error(E_EXTRA_CHARS, current));
	return (E_SUCCESS);
}
	// xyz - [f], [f], [f]
	// xyz_3d - [-1,1], [-1,1], [-1,1]
	// fov - [0-180]

int	process_camera(t_list *current)
{
	int	status;

	status = 0;
	status = process_xyz(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_xyz_3d(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_fov(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (ret_error(E_EXTRA_CHARS, current));
	return (E_SUCCESS);
}
	// xyz - [f], [f], [f]
	// xyz_3d - [-1,1], [-1,1], [-1,1]
	// cd - [f]
	// ch - [f]
	// rgb - [0-255], [0-255], [0-255]

int	process_cylinder(t_list *current)
{
	int	status;

	status = process_xyz(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_xyz_3d(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_cd(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_ch(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_rgb(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	return (status);
}
	// xyz - [f], [f], [f]
	// xyz_3d - [-1,1], [-1,1], [-1,1]
	// rgb - [0-255], [0-255], [0-255]

void	process_plane(t_list *current)
{
	process_xyz(current);
	process_xyz_3d(current);
	process_rgb(current);
}

	// xyz - [f], [f], [f]
	// lbr - [0-1]
	// rgb - [0-255], [0-255], [0-255]
int	process_light(t_list *current)
{
	int	status;

	status = 0;
	status = process_xyz(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_lbr(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	status = process_rgb(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (ret_error(E_EXTRA_CHARS, current));
	return (E_SUCCESS);
}
