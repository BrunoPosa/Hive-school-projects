/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:41:28 by ohertzbe          #+#    #+#             */
/*   Updated: 2024/08/28 12:30:09 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static int	sphere_shadow(t_rt rt, int *in_shadow, t_hit_record h_rec)
{
	int	i;

	i = -1;
	while (++i < rt.num_sp)
	{
		if (hit_sphere(rt.sp[i].center, rt.sp[i].radius, rt.l.shadow_ray) > 0.0)
		{
			if (h_rec.shape == 0 && h_rec.id == i)
				continue ;
			*in_shadow = 1;
			return (1);
		}
	}
	return (0);
}

static int	cylinder_shadow(t_rt rt, int *in_shadow, t_hit_record h_rec)
{
	int	i;

	i = -1;
	while (++i < rt.num_cy)
	{
		if (hit_cylinder(rt.cy[i], rt.l.shadow_ray) > 0.0)
		{
			if (h_rec.shape == 2 && h_rec.id == i)
				continue ;
			*in_shadow = 1;
			return (1);
		}
	}
	return (0);
}

static void	plane_shadow(t_rt rt, int *in_shadow, t_hit_record h_rec)
{
	int		i;
	float	t_hit;
	float	light_dist;

	i = -1;
	while (++i < rt.num_pl)
	{
		t_hit = hit_plane(rt.pl[i].normal, rt.pl[i].point, rt.l.shadow_ray);
		if (t_hit > 0.0)
		{
			light_dist = vec_len(rt.l.light_dir);
			if (t_hit < light_dist)
			{
				if (h_rec.shape == 1 && h_rec.id == i)
					continue ;
				*in_shadow = 1;
				return ;
			}
		}
	}
}

void	check_shadow(t_rt rt, int *in_shadow, t_hit_record h_rec)
{
	rt.l.shadow_ray.start = h_rec.point;
	rt.l.shadow_ray.direction = rt.l.light_dir;
	*in_shadow = 0;
	if (sphere_shadow(rt, in_shadow, h_rec) == 1)
		return ;
	if (cylinder_shadow(rt, in_shadow, h_rec) == 1)
		return ;
	plane_shadow(rt, in_shadow, h_rec);
}
