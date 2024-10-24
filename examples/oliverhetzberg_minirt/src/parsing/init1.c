/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:04:14 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 15:01:45 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

void	init_light(t_rt *rt)
{
	rt->l.id = 0;
	init_vector(&rt->l.point);
	rt->l.bright = 0.0;
	init_vector(&rt->l.col);
}

void	init_sphere(t_rt *rt)
{
	int	i;

	i = 0;
	rt->sp = (t_sphere *)malloc(sizeof(t_sphere) * rt->num_sp);
	if (!(rt->sp))
		malloc_error();
	while (i < rt->num_sp)
	{
		rt->sp[i].id = 0;
		init_vector(&rt->sp[i].center);
		rt->sp[i].radius = 0.0;
		init_vector(&rt->sp[i].col);
		i++;
	}
}

void	init_plane(t_rt *rt)
{
	int	i;

	i = 0;
	rt->pl = (t_plane *)malloc(sizeof(t_plane) * rt->num_pl);
	if (!(rt->pl))
		malloc_error();
	while (i < rt->num_pl)
	{
		rt->pl[i].id = 0;
		init_vector(&rt->pl[i].point);
		init_vector(&rt->pl[i].normal);
		init_vector(&rt->pl[i].col);
		i++;
	}
}

void	init_cylinder(t_rt *rt)
{
	int	i;

	i = 0;
	rt->cy = (t_cylinder *)malloc(sizeof(t_cylinder) * rt->num_cy);
	if (!(rt->cy))
		malloc_error();
	while (i < rt->num_cy)
	{
		rt->cy[i].id = 0;
		init_vector(&rt->cy[i].center);
		init_vector(&rt->cy[i].axis);
		rt->cy[i].radius = 0.0;
		rt->cy[i].height = 0.0;
		init_vector(&rt->cy[i].col);
		i++;
	}
}
