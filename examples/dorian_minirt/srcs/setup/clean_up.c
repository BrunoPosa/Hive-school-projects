/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 17:52:19 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		i++;
	}
	if (scene->objs)
		free(scene->objs);
	if (scene->lights)
		free(scene->lights);
	if (scene->distances)
		free(scene->distances);
	if (scene->directions)
		free(scene->directions);
}

void	free_img(t_img *img)
{
	if (img->img)
		mlx_destroy_image(img->win.mlx, img->img);
	if (img->win.win)
		mlx_destroy_window(img->win.mlx, img->win.win);
	if (img->scene->objs)
		free_scene(img->scene);
}
