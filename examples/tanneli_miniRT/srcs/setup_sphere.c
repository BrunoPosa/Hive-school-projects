/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:59:52 by tvalimak          #+#    #+#             */
/*   Updated: 2024/08/19 14:56:38 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static t_sphere	*setup_sphere_helper(t_map *map)
{
	t_sphere	*temp;

	if (!map->sphere)
	{
		printf("inside setup_sphere_helper 1\n");
		map->sphere = malloc(sizeof(t_sphere));
		if (!map->sphere)
			return (NULL);
		map->sphere->next = NULL;
	}
	else
	{
		printf("inside setup_sphere_helper 2\n");
		temp = map->sphere;
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_sphere));
		if (temp->next == NULL)
			return (NULL);
		temp->next->next = NULL;
		return temp->next;
	}
	return map->sphere;
}

/*identifier: sp
∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
∗ the sphere diameter: 12.6
∗ R,G,B colors in range [0-255]: 10, 0, 255*/

int	setup_sphere(char **split, t_map *map)
{
	char	**rgb;
    char    **xyz;
    t_sphere  *new_sphere;

	printf("inside setup_sphere\n");
	new_sphere = setup_sphere_helper(map);
	rgb = ft_split(split[3], ',');
    xyz = ft_split(split[1], ',');
    new_sphere->x = ft_atof(xyz[0]);
    new_sphere->y = ft_atof(xyz[1]);
    new_sphere->z = ft_atof(xyz[2]);
    new_sphere->diameter = ft_atof(split[2]);
    new_sphere->r = ft_atoi(rgb[0]);
    new_sphere->g = ft_atoi(rgb[1]);
    new_sphere->b = ft_atoi(rgb[2]);
	free_split(rgb);
    free_split(xyz);
	printf("end of setup_sphere\n");
	return (1);
}
