/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:22:43 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/24 17:35:23 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static t_bool	check_cap(float **ray, float t, float y)
{
	float	x;
	float	z;

	x = ray[0][0] + t * ray[1][0];
	z = ray[0][2] + t * ray[1][2];
	if (x * x + z * z <= fabs(y))
		return (TRUE);
	else
		return (FALSE);
}

static t_inters	*intersect_caps(t_object *cone, float **ray, t_inters *xs)
{
	float	t;

	if (cone->closed == FALSE || fabs(ray[1][1]) < EPS)
		return (xs);
	t = (cone->cylindermin - ray[0][1]) / ray[1][1];
	if (check_cap(ray, t, cone->cylindermin))
	{
		xs->count++;
		xs->t[xs->count - 1] = t;
		xs->objects[xs->count - 1] = cone;
	}
	t = (cone->cylindermax - ray[0][1]) / ray[1][1];
	if (check_cap(ray, t, cone->cylindermax))
	{
		xs->count++;
		xs->t[xs->count - 1] = t;
		xs->objects[xs->count - 1] = cone;
	}
	xs->objects[xs->count] = NULL;
	return (xs);
}

static t_inters	*check_height(t_cylvals *v, t_object *cone, float **ray)
{
	t_inters	*xs;

	xs = create_intersections(5);
	if (!xs)
		return (NULL);
	v->y0 = ray[0][1] + v->t0 * ray[1][1];
	if (cone->cylindermin < v->y0 && v->y0 < cone->cylindermax)
	{
		xs->count++;
		xs->t[xs->count - 1] = v->t0;
		xs->objects[xs->count - 1] = cone;
	}
	v->y1 = ray[0][1] + v->t1 * ray[1][1];
	if (cone->cylindermin - EPS < v->y1 && v->y1 <= cone->cylindermax + EPS)
	{
		xs->count++;
		xs->t[xs->count - 1] = v->t1;
		xs->objects[xs->count - 1] = cone;
	}
	return (intersect_caps(cone, ray, xs));
}

t_inters	*cone_intersect(t_object *cone, float **ray)
{
	t_cylvals	v;

	v.t0 = -1;
	v.t1 = -1;
	v.a = pow(ray[1][0], 2) - pow(ray[1][1], 2) + pow(ray[1][2], 2);
	v.b = 2 * ray[0][0] * ray[1][0] - 2 * ray[0][1] * ray[1][1]
		+ 2 * ray[0][2] * ray[1][2];
	v.c = pow(ray[0][0], 2) - pow(ray[0][1], 2) + pow(ray[0][2], 2);
	if (equal_float(v.a, 0) == 1)
	{
		if (equal_float(v.b, 0) == 0)
			v.t0 = -v.c / (2 * v.b);
		return (check_height(&v, cone, ray));
	}
	v.disc = pow(v.b, 2) - (4 * v.a * v.c);
	if (fabs(v.disc) < EPS)
		v.disc = 0;
	if (v.disc < 0)
		return (NULL);
	v.t0 = ((-v.b) - sqrt(v.disc)) / (2 * v.a);
	v.t1 = ((-v.b) + sqrt(v.disc)) / (2 * v.a);
	if (v.t0 > v.t1)
		ft_swap(&v.t0, &v.t1);
	return (check_height(&v, cone, ray));
}
