/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:34:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

t_inters	*create_intersections(int n)
{
	t_inters	*inter;
	int			i;

	i = -1;
	inter = malloc(sizeof(t_inters));
	if (!inter)
		return (NULL);
	inter->count = 0;
	inter->objects = malloc(n * 4 * sizeof(t_object *));
	if (!inter->objects)
	{
		free(inter);
		return (NULL);
	}
	inter->t = malloc(n * 4 * sizeof(float));
	if (!inter->t)
	{
		free(inter->objects);
		free(inter);
		return (NULL);
	}
	while (++i < (n * 4))
		inter->objects[i] = NULL;
	return (inter);
}

t_comp	*create_comp(t_inter *i)
{
	t_comp	*comp;

	comp = malloc(sizeof(t_comp));
	if (!comp)
		return (NULL);
	comp->point = NULL;
	comp->over_point = NULL;
	comp->eyev = NULL;
	comp->normalv = NULL;
	comp->t = i->t;
	comp->object = i->object;
	return (comp);
}

t_material	*create_material(t_parse *parse)
{
	t_material	*mat;

	mat = malloc(sizeof(t_material));
	if (!mat)
		return (NULL);
	mat->color = color(0, 0, 0);
	if (!mat->color)
	{
		free(mat);
		return (NULL);
	}
	mat->ambient = color(parse->amcolor[0],
			parse->amcolor[1], parse->amcolor[2]);
	mat->diffuse = 0.9;
	mat->specular = 0.9;
	mat->shininess = 200;
	mat->pattern = FALSE;
	mat->patt = NULL;
	return (mat);
}

t_object	*create_object(t_shape shape, t_parse *parse)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->s = shape;
	obj->diameter = 2;
	obj->height = 1;
	obj->coord = create_point(0, 0, 0);
	obj->material = create_material(parse);
	obj->normv = create_vector(0, 0, 0);
	obj->transform = create_identity(4);
	obj->cylindermin = 0;
	obj->cylindermax = 1;
	obj->closed = TRUE;
	obj->bump = FALSE;
	if (!obj->coord || !obj->material
		|| !obj->normv || !obj->transform)
	{
		clean_object(obj);
		return (NULL);
	}
	return (obj);
}

t_world	*create_world(int n, t_light **lights)
{
	t_world	*world;

	if (!lights)
		return (NULL);
	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->number_objects = n;
	world->objects = NULL;
	world->lights = lights;
	return (world);
}
