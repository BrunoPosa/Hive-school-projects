/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:44:58 by ohertzbe          #+#    #+#             */
/*   Updated: 2024/08/27 23:38:08 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/*
	focal_length = distance from camera to viewport

	camera_forward given from the scene rt->c.or_vec

	camera right we get by calculating the cross product of {0, 1, 0} vector
	and camera_forward.

	camera up is calculated from the crossproduct of camera right and camera forward

	viewport_u = vector of whole width of viewport
	viewport_v = vector of whole height of viewport

	rt->c.pixel00_loc = our topleft corner pixel on our viewport
*/
void	initialize_camera(t_rt *rt)
{
	t_init_cam	i;

	rt->aspect_ratio = (float) WIDTH / HEIGHT;
	i.focal_length = (rt->width / 2) / (tanf((rt->c.fov * (PI / 180)) / 2));
	i.viewport_w = rt->width * 2;
	i.viewport_h = i.viewport_w / rt->aspect_ratio;
	i.camera_f = unit_vec(rt->c.or_vec);
	if (vec_len(cross_prod((t_vec){0, 1, 0}, i.camera_f)) != 0)
		i.camera_r = unit_vec(cross_prod((t_vec){0, 1, 0}, i.camera_f));
	else
		i.camera_r = unit_vec(cross_prod((t_vec){0, 1, -0.00001}, i.camera_f));
	i.camera_up = cross_prod(i.camera_f, i.camera_r);
	i.viewport_u = vec_mult(i.camera_r, i.viewport_w);
	i.viewport_v = vec_mult(i.camera_up, i.viewport_h);
	rt->c.px_delta_u = vec_div(i.viewport_u, rt->width);
	rt->c.px_delta_v = vec_div(i.viewport_v, rt->height);
	i.focal = vec_mult(i.camera_f, i.focal_length);
	i.viewport_up_l = vec_sub(rt->c.point, i.focal);
	i.viewport_up_l = vec_sub(i.viewport_up_l, vec_div(i.viewport_u, 2));
	i.viewport_up_l = vec_sub(i.viewport_up_l, vec_div(i.viewport_v, 2));
	rt->c.px00loc = vec_mult(vec_add(rt->c.px_delta_u, rt->c.px_delta_v), 0.5);
	rt->c.px00loc = vec_add(rt->c.px00loc, i.viewport_up_l);
}

static void	close_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	initialize_mlx(t_rt *rt)
{
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", true);
	if (!rt->mlx)
	{
		printf("mlx_init failed\n");
		free_all(rt);
		exit(1);
	}
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
	{
		printf("mlx_new_image failed\n");
		free_all(rt);
		exit(1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
	{
		printf("mlx_image_to_window failed\n");
		free_all(rt);
		exit(1);
	}
	mlx_loop_hook(rt->mlx, &close_hook, rt->mlx);
}

void	render_scene(t_rt rt)
{
	t_render	r;

	r.y = -1;
	while (++r.y < rt.height)
	{
		r.x = -1;
		while (++r.x < rt.width)
		{
			r.px_center = vec_add(rt.c.px00loc, vec_mult(rt.c.px_delta_u, r.x));
			r.px_center = vec_add(r.px_center, vec_mult(rt.c.px_delta_v, r.y));
			r.ray_direction = unit_vec(vec_sub(r.px_center, rt.c.point));
			if (dot_prod(r.ray_direction, rt.c.or_vec) < 0)
			{
				r.ray_direction = vec_mult(r.ray_direction, -1.0);
			}
			r.ray = init_ray(rt.c.point, r.ray_direction);
			r.color = ray_color(r.ray, rt);
			r.rgba = get_rgba(r.color.x, r.color.y, r.color.z, 255);
			set_px_col(rt.img, r.x, r.y, r.rgba);
		}
	}
}

int	main(int argc, char **argv)
{
	t_rt	rt;
	int		fd;
	t_index	j;

	check_args(argc, argv);
	init_rt(&rt, &j, argv);
	fd = open_file(argv[1]);
	if (parse_rt(&rt, fd, &j) == 0)
	{
		free_pars(&rt);
		close(fd);
		return (1);
	}
	close(fd);
	initialize_camera(&rt);
	initialize_mlx(&rt);
	render_scene(rt);
	mlx_loop(rt.mlx);
	free_all(&rt);
	return (0);
}
