/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/27 10:44:11 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_arrays(t_object object)
{
	int	i;

	if (object.mesh.vertex)
		free(object.mesh.vertex);
	if (object.mesh.normals)
		free(object.mesh.normals);
	if (object.mesh.count_vt != 0)
		free(object.mesh.textures);
	i = 0;
	while (i < object.mesh.count_f)
	{
		free(object.mesh.faces[i]);
		i++;
	}
	if (object.mesh.faces)
		free(object.mesh.faces);
	if (object.mesh.triangle_data)
		free(object.mesh.triangle_data);
}

void	free_scene_arrays(t_scene *scene)
{
	if (scene->objs)
		free(scene->objs);
	if (scene->lights)
		free(scene->lights);
	if (scene->specular)
		free(scene->specular);
	if (scene->distances)
		free(scene->distances);
	if (scene->directions)
		free(scene->directions);
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->n_objs)
	{
		if (scene->objs[i].type == cylinder_obj)
		{
			free(scene->objs[i].cylinder.top);
			free(scene->objs[i].cylinder.bottom);
		}
		if (scene->objs[i].type == cone_obj)
			free(scene->objs[i].cone.bottom);
		if (scene->objs[i].meta.tex_col)
			free(scene->objs[i].meta.tex_col);
		if (scene->objs[i].meta.tex_norm)
			free(scene->objs[i].meta.tex_norm);
		if (scene->objs[i].type == mesh_obj)
			free_arrays(scene->objs[i]);
		i++;
	}
	free_scene_arrays(scene);
}

void	free_img(t_img *img)
{
	if (img->scene)
		free_scene(img->scene);
	if (img->img)
		mlx_destroy_image(img->win.mlx, img->img);
	if (img->win.win)
		mlx_destroy_window(img->win.mlx, img->win.win);
}
