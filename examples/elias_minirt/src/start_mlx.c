/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:48:15 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 10:08:35 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static	t_rtx	*create_rtx(t_camera *c, t_world *w)
{
	t_rtx	*rtx;

	rtx = malloc(sizeof(t_rtx));
	if (!rtx)
		return (NULL);
	rtx->cam = c;
	rtx->world = w;
	rtx->resize = 0;
	rtx->time = mlx_get_time();
	return (rtx);
}

void	start_display(t_camera *c, t_world *w)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_rtx		*rtx;

	mlx = mlx_init(c->hsize, c->vsize, "miniRT", true);
	if (!mlx)
		exit(1);
	img = mlx_new_image(mlx, c->hsize, c->vsize);
	if (!img)
	{
		mlx_terminate(mlx);
		exit(1);
	}
	rtx = create_rtx(c, w);
	if (!rtx)
		exit (1);
	rtx->img = img;
	mlx_image_to_window(mlx, img, 0, 0);
	render(c, w, img);
	mlx_key_hook(mlx, &my_keyhook, mlx);
	mlx_loop_hook(mlx, &resize, rtx);
	mlx_resize_hook(mlx, &resize_hook, rtx);
	mlx_loop(mlx);
	clean_rtx(rtx, mlx, img);
}
