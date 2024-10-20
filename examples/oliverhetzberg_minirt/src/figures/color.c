/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:39:27 by ohertzbe          #+#    #+#             */
/*   Updated: 2024/08/28 13:35:02 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	check_spheres(t_ray ray, t_rt rt, t_hit_record *h_rec)
{
	int		i;
	float	t;

	h_rec->t = -1;
	i = -1;
	while (++i < rt.num_sp)
	{
		t = hit_sphere(rt.sp[i].center, rt.sp[i].radius, ray);
		if (i == 0 || (t > 0.0 && (h_rec->t < 0.0 || t < h_rec->t)))
		{
			h_rec->t = t;
			h_rec->point = ray_point(ray, t);
			h_rec->normal = unit_vec(vec_sub(h_rec->point, rt.sp[i].center));
			h_rec->color = vec_mult(rt.sp[i].col, 255);
			h_rec->center = rt.sp[i].center;
			h_rec->id = i;
			h_rec->shape = 0;
		}
	}
}

void	check_planes(t_ray ray, t_rt rt, t_hit_record *h_rec)
{
	int		i;
	float	t;

	i = -1;
	while (++i < rt.num_pl)
	{
		t = hit_plane(rt.pl[i].normal, rt.pl[i].point, ray);
		if ((i == 0 && rt.num_sp == 0)
			|| (t > 0.0 && (h_rec->t < 0.0 || t < h_rec->t)))
		{
			h_rec->t = t;
			h_rec->point = ray_point(ray, t);
			h_rec->normal = rt.pl[i].normal;
			h_rec->color = vec_mult(rt.pl[i].col, 255);
			h_rec->center = rt.pl[i].point;
			h_rec->id = i;
			h_rec->shape = 1;
		}
	}
}

void	check_cylinders(t_ray ray, t_rt rt, t_hit_record *h_rec)
{
	int		i;
	float	t;

	i = -1;
	while (++i < rt.num_cy)
	{
		t = hit_cylinder(rt.cy[i], ray);
		if ((i == 0 && (rt.num_sp == 0 && rt.num_pl == 0))
			|| (t > 0.0 && (h_rec->t < 0.0 || t < h_rec->t)))
		{
			h_rec->t = t;
			h_rec->point = ray_point(ray, t);
			h_rec->normal = cyl_normal(h_rec->point,
					rt.cy[i], rt.cy[i].height, rt.cy[i].radius);
			h_rec->color = vec_mult(rt.cy[i].col, 255);
			h_rec->center = rt.cy[i].center;
			h_rec->id = i;
			h_rec->shape = 2;
		}
	}
}

/*
	Computes diffuse and specular lighting
	according to the Phong reflection model
	https://en.wikipedia.org/wiki/Phong_reflection_model
*/
void	compute_lighting(t_vec *color, t_rt rt, t_hit_record h_rec)
{
	float		diffuse_strength;
	t_vec		diffuse;

	rt.l.light_color = (t_vec){1.0, 1.0, 1.0};
	rt.l.lighting = (t_vec){1.0, 1.0, 1.0};
	diffuse_strength = fmaxf(0.0, dot_prod(rt.l.light_dir, h_rec.normal));
	diffuse = vec_mult(rt.l.light_color, diffuse_strength);
	rt.l.lighting = vec_add(vec_mult((t_vec)
			{rt.a.ratio, rt.a.ratio, rt.a.ratio}, 0.5),
			vec_mult(diffuse, rt.l.bright));
	*color = (t_vec){h_rec.color.x * rt.l.lighting.x,
		h_rec.color.y * rt.l.lighting.y, h_rec.color.z * rt.l.lighting.z};
	color->x = fminf(fmaxf(color->x, 0.0), 255.0);
	color->y = fminf(fmaxf(color->y, 0.0), 255.0);
	color->z = fminf(fmaxf(color->z, 0.0), 255.0);
}

t_vec	ray_color(t_ray ray, t_rt rt)
{
	t_hit_record	h_rec;
	int				in_shadow;
	t_vec			color;

	check_spheres(ray, rt, &h_rec);
	check_planes(ray, rt, &h_rec);
	check_cylinders(ray, rt, &h_rec);
	if (h_rec.t > 0.0)
	{
		rt.l.light_dir = unit_vec(vec_sub(rt.l.point, h_rec.point));
		check_shadow(rt, &in_shadow, h_rec);
		compute_lighting(&color, rt, h_rec);
		if (in_shadow == 1)
			color = vec_mult(color, (1.0 - ((rt.l.bright * 0.5)
							+ (rt.a.ratio * 0.5))));
		return (color);
	}
	return ((t_vec){0, 0, 0});
}
