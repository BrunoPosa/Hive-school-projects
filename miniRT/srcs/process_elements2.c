/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:53 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 22:14:19 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!
// xyz - [f], [f], [f]
// sd - [f]
// rgb - [0-255], [0-255], [0-255]

void	process_sphere(t_list *current)
{
	process_xyz(current);
	process_sd(current);
	process_rgb(current);
}
