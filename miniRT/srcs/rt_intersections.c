/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:59:49 by bposa             #+#    #+#             */
/*   Updated: 2024/12/26 03:55:53 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
	'a' of the quadratic formula is 1, as 'ray' is a normalized vector,
	so we leave it out
*/
float	fsphere(t_vec ray, t_vec origin, t_shape *sphere)
{
	t_vec	origin_to_sphere_xyz;
	float	t;
	float	b;
	float	c;
	float	discriminant;

	origin_to_sphere_xyz = subtract(origin, sphere->xyz);
	t = -1.0f;
	b = 2 * dot(ray, origin_to_sphere_xyz);
	c = dot(origin_to_sphere_xyz, origin_to_sphere_xyz) - sphere->r * sphere->r;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (-1);
	t = (-b - sqrt(discriminant)) / 2;
	if (t < EPSILON)
	{
		t = (-b + sqrt(discriminant)) / 2;
		if (t > EPSILON)
			sphere->inside = true;
	}
	return (t);
}

float	fplane(t_vec ray, t_vec origin, t_shape *plane)
{
	t_vec	origin_to_plane;
	float	dividend;
	float	divisor;
	float	t;

	origin_to_plane = subtract(plane->xyz, origin);
	dividend = dot(plane->axis, origin_to_plane);
	divisor = dot(ray, plane->axis);
	if (fabs(divisor) < EPSILON)
		return (-1.0);
	t = dividend / divisor;
	if (t < EPSILON)
		return (-1.0);
	return (t);
}

/*
	Returns minimum positive distance t if ray intersects the cylinder;
	Sets 'shape->part_hit' to top, bottom, or body. Returns < 0 if ray misses.
*/
float	fcylinder(t_vec ray, t_vec origin, t_shape *cyl)
{
	t_vec	oc;
	float	coef[3];
	float	discriminant;
	float	t;
	float	tcaps;

	oc = subtract(origin, cyl->xyz);
	coef[a] = dot(ray, ray) - (pow(dot(ray, cyl->axis), 2));
	coef[b] = 2 * (dot(ray, oc) - (dot(ray, cyl->axis) * dot(oc, cyl->axis)));
	coef[c] = dot(oc, oc) - pow(dot(oc, cyl->axis), 2) - cyl->r * cyl->r;
	discriminant = coef[b] * coef[b] - 4 * coef[a] * coef[c];
	if (discriminant < 0)
		return (-1);
	t = (-coef[b] - sqrt(discriminant)) / (2 * coef[a]);
	if (t < EPSILON)
		t = (-coef[b] + sqrt(discriminant)) / (2 * coef[a]);
	t = cyl_height_check(ray, origin, t, cyl);
	tcaps = intersect_cyl_caps(ray, origin, cyl);
	if (t > EPSILON && (tcaps < EPSILON || t < tcaps))
	{
		cyl->part_hit = body;
		return (t);
	}
	return (tcaps);
}

float	intersect_cyl_caps(t_vec ray, t_vec origin, t_shape *cyl)
{
	t_shape	cap;
	t_shape	base;
	float	t_top;
	float	t_base;

	cap = *cyl;
	base = *cyl;
	cap.xyz = add(cyl->xyz, scale(cyl->axis, cyl->h));
	base.axis = negate(cyl->axis);
	t_top = cyl_radius_check(ray, origin, fplane(ray, origin, &cap), &cap);
	t_base = cyl_radius_check(ray, origin, fplane(ray, origin, &base), &base);
	if (t_top > EPSILON && (t_base < EPSILON || t_top < t_base))
	{
		cyl->part_hit = top;
		return (t_top);
	}
	else
	{
		cyl->part_hit = bottom;
		return (t_base);
	}
}

/*
	Returns 0 if hitpoint at t is out of vertical cylinder bounds, or if
	t <= EPSILON. Returns unmodified t if within bounds.
*/
float	cyl_height_check(t_vec ray, t_vec origin, float t, t_shape *cyl)
{
	t_vec	hitpoint;
	float	projection;

	ft_memset(&hitpoint, 0, sizeof(t_vec));
	if (t <= EPSILON || !cyl)
		return (0.0f);
	hitpoint = add(origin, scale(ray, t));
	projection = dot(subtract(hitpoint, cyl->xyz), cyl->axis);
	if (projection < 0 || projection > cyl->h)
		return (0.0f);
	return (t);
}
