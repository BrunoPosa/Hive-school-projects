/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:53 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 22:00:35 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!


void process_sphere(t_list *current)
{
	// printf("\nPROCESS SHPERE\n");
	// printf("data = %s\n", current->p);

	// xyz - [f], [f], [f]
	process_xyz(current);

	// sd - [f]
	process_sd(current);

	// rgb - [0-255], [0-255], [0-255]
	process_rgb(current);

	// ft_anything_else_in_string_say_no(current->p);
}