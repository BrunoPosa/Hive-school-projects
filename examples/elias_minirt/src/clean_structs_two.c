/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:47:20 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 12:19:30 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	clean_parse(t_parse *parse)
{
	if (parse->amcolor)
		free(parse->amcolor);
	if (parse->lightnumb > 0)
		clean_lights(parse->light);
	free(parse);
}

void	clean_world(t_world	*w)
{
	int	n;

	n = 0;
	if (w)
	{
		while (n < w->number_objects)
		{
			if (w->objects[n])
				clean_object(w->objects[n]);
			n++;
		}
		free(w->objects);
		free(w);
	}
	w = NULL;
}

void	clean_ray(float **ray)
{
	if (ray[0])
		free(ray[0]);
	if (ray[1])
		free(ray[1]);
	if (ray)
		free(ray);
}

void	clean_points(float *a, float *b, float *c, float *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
}

void	clean_rtx(t_rtx	*rtx, mlx_t	*mlx, mlx_image_t *img)
{
	clean_matrix(rtx->cam->transform, 4);
	free(rtx->cam);
	free(rtx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
