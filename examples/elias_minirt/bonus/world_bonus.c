/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:52:53 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

static t_inters	*combine_xs(t_inters *a, t_inters *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a->objects[i])
		i++;
	while (b->objects[j])
	{
		a->t[i] = b->t[j];
		a->objects[i] = b->objects[j];
		a->count++;
		i++;
		j++;
	}
	a->objects[i] = NULL;
	clean_intersections(b);
	return (a);
}

t_inters	*intersect_world(t_world *w, float **r)
{
	t_inters	*w_inters;
	t_inters	*temp;
	int			i;

	i = -1;
	w_inters = create_intersections(w->number_objects);
	if (!w_inters)
		return (NULL);
	while (++i < w->number_objects)
	{
		temp = pre_intersect(w->objects[i], r);
		if (temp)
			combine_xs(w_inters, temp);
	}
	sort_intersect(w_inters);
	return (w_inters);
}

static void	get_over_point(t_comp *comp)
{
	float	*tmp;

	tmp = scalar_multi_tuple(comp->normalv, 0.001);
	comp->over_point = tuple_add(comp->point, tmp);
	free(tmp);
}

t_comp	*prepare_computations(t_inter *i, float **ray)
{
	t_comp	*comp;
	float	*tmp;

	comp = create_comp(i);
	if (!comp)
		return (NULL);
	comp->point = ray_position(ray, comp->t);
	comp->eyev = negate_vector(ray[1]);
	comp->normalv = normal_at(comp->object, comp->point);
	if (!comp->point || !comp->eyev || !comp->normalv)
	{
		clean_comp(comp);
		return (NULL);
	}
	if (dot_product(comp->normalv, comp->eyev) < 0)
	{
		comp->inside = TRUE;
		tmp = comp->normalv;
		comp->normalv = negate_vector(comp->normalv);
		free(tmp);
	}
	else
		comp->inside = FALSE;
	get_over_point(comp);
	return (comp);
}
