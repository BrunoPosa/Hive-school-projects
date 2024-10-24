/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:36:08 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

static t_lightdot	*light_pre(t_lightdot *ldot)
{
	ldot->eff_color = hadamard(ldot->obj->material->color, ldot->l->color);
	if (!ldot->eff_color)
		return (NULL);
	ldot->tmp = tuple_subs(ldot->l->coord, ldot->comp->over_point);
	if (!ldot->tmp)
	{
		free(ldot->eff_color);
		return (NULL);
	}
	ldot->lightv = normalize(ldot->tmp, 1);
	if (!ldot->lightv)
	{
		free(ldot->eff_color);
		return (NULL);
	}
	return (ldot);
}

float	*shade_hit(t_world	*w, t_comp *comp)
{
	int		n;
	int		i;
	float	*col;
	float	*result;

	i = 0;
	result = color(0, 0, 0);
	while (result && w->lights[i])
	{
		n = is_shadowed(w, comp->over_point, w->lights[i]);
		if (comp->object->material->pattern == TRUE)
			comp->object->material->color = checker_at_obj(comp);
		col = lighting(comp, w->lights[i], comp->object, n);
		if (!col)
		{
			free(result);
			return (NULL);
		}
		result = add_two_colors(result, col);
		i++;
	}
	return (result);
}

float	*color_at(t_world *w, float **ray)
{
	t_inters	*xs;
	t_inter		*i;
	t_comp		*comp;
	float		*result;

	xs = intersect_world(w, ray);
	if (!xs)
		return (NULL);
	i = hit(xs);
	clean_intersections(xs);
	if (!i)
		return (NULL);
	if (i->t == -1)
	{
		free(i);
		return (color(0, 0, 0));
	}
	comp = prepare_computations(i, ray);
	if (comp->object->bump == TRUE)
		comp->normalv = perturb_normal(comp->normalv, comp->over_point);
	result = shade_hit(w, comp);
	free(i);
	clean_comp(comp);
	return (result);
}

static float	*specular(float *lv, t_comp *comp, t_object *obj, t_light *l)
{
	float	*tmp;
	float	*reflectv;
	float	ref_dot_eye;
	float	factor;

	tmp = negate_vector(lv);
	if (!tmp)
		return (NULL);
	reflectv = reflect(tmp, comp->normalv);
	free(tmp);
	if (!reflectv)
		return (NULL);
	ref_dot_eye = dot_product(reflectv, comp->eyev);
	free(reflectv);
	if (ref_dot_eye < 0)
		return (color(0, 0, 0));
	else
	{
		factor = pow(ref_dot_eye, obj->material->shininess);
		tmp = multiply_color(l->color, obj->material->specular, 0);
	}
	return (multiply_color(tmp, factor, 1));
}

float	*lighting(t_comp *comp, t_light *l, t_object *obj, int shadow)
{
	t_lightdot	ldot;

	ldot.comp = comp;
	ldot.l = l;
	ldot.obj = obj;
	if (!light_pre(&ldot))
		return (NULL);
	ldot.ambient = hadamard(ldot.eff_color, obj->material->ambient);
	ldot.light_dot_nor = dot_product(ldot.lightv, comp->normalv);
	if (ldot.light_dot_nor < 0 || shadow)
	{
		ldot.diffuse = color(0, 0, 0);
		ldot.spec = color(0, 0, 0);
		free(ldot.eff_color);
	}
	else
	{
		ldot.tmp = multiply_color(ldot.eff_color, obj->material->diffuse, 1);
		ldot.diffuse = multiply_color(ldot.tmp, ldot.light_dot_nor, 1);
		ldot.spec = specular(ldot.lightv, comp, obj, l);
	}
	free(ldot.lightv);
	return (add_colors(ldot.ambient, ldot.diffuse, ldot.spec));
}
