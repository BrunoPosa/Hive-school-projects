/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:06:26 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:20:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	clean_lights(t_light **lights)
{
	int	i;

	i = 0;
	if (lights)
	{
		while (lights[i])
		{
			if (lights[i]->coord)
				free(lights[i]->coord);
			if (lights[i]->color)
				free(lights[i]->color);
			free(lights[i]);
			i++;
		}
		free(lights);
	}
	lights = NULL;
}

void	clean_intersections(t_inters *inter)
{
	if (inter)
	{
		if (inter->objects)
			free(inter->objects);
		if (inter->t)
			free(inter->t);
		free(inter);
	}
	inter = NULL;
}

void	clean_comp(t_comp *comp)
{
	if (comp)
	{
		if (comp->point)
			free(comp->point);
		if (comp->eyev)
			free(comp->eyev);
		if (comp->normalv)
			free(comp->normalv);
		if (comp->over_point)
			free(comp->over_point);
		free(comp);
	}
	comp = NULL;
}

void	clean_material(t_material *mat)
{
	if (mat)
	{
		if (mat->color && mat->pattern == FALSE)
			free(mat->color);
		if (mat->ambient)
			free(mat->ambient);
		if (mat->pattern == TRUE)
		{
			if (!mat->patt)
			{
				free(mat->patt->colora);
				free(mat->patt->colorb);
				clean_matrix(mat->patt->transf, 4);
				free(mat->patt);
			}
		}
		free(mat);
	}
	mat = NULL;
}

void	clean_object(t_object *obj)
{
	if (obj)
	{
		if (obj->coord)
			free(obj->coord);
		if (obj->normv)
			free(obj->normv);
		if (obj->material)
			clean_material(obj->material);
		if (obj->transform)
			clean_matrix(obj->transform, 4);
		free(obj);
	}
	obj = NULL;
}
