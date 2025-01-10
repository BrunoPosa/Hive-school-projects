/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:38 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_ambiant(t_list *current)
{
	int	status;

	status = process_alr(current);
	if (status)
		return (status);
	status = process_rgb(current);
	if (status)
		return (status);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (E_EXTRA_CHARS);
	return (status);
}

int	process_camera(t_list *current)
{
	int	status;

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

int	process_cylinder(t_list *current)
{
	int	status;

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
	return (process_rgb(current));
}

int	process_plane(t_list *current)
{
	int	status;

	status = process_xyz(current);
	if (status)
		return (status);
	status = process_xyz_3d(current);
	if (status)
		return (status);
	return (process_rgb(current));
}

int	process_light(t_list *current)
{
	int	status;

	status = process_xyz(current);
	if (status)
		return (status);
	status = process_lbr(current);
	if (status)
		return (status);
	status = process_rgb(current);
	if (status)
		return (status);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (E_EXTRA_CHARS);
	return (status);
}
