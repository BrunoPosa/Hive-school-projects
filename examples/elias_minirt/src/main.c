/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:47:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 14:04:39 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	check_extras(t_object **objects, t_parse *parse)
{
	int	i;

	i = -1;
	while (++i < parse->total)
	{
		if (objects[i]->material->pattern == TRUE || parse->lightnumb > 1
			|| objects[i]->s == CONE)
		{
			i = -1;
			while (++i < parse->total)
				clean_object(objects[i]);
			free (objects);
			clean_parse(parse);
			ft_printf(2, "Error\nwith parsing\n");
			exit (1);
		}
	}
}

static t_parse	*init_parse(void)
{
	t_parse		*parse;

	parse = malloc(sizeof(t_parse));
	parse->lightnumb = 0;
	parse->total = 0;
	parse->amcolor = create_point(0, 0, 0);
	parse->amnum = 0;
	parse->cnum = 0;
	parse->light = NULL;
	return (parse);
}

static float	*compute_up(float *dir)
{
	float	*temp_up;
	float	*right;
	float	*cameradir;
	float	*up;

	cameradir = create_vector(dir[0], dir[1], dir[2]);
	if (fabs(dir[1]) < 0.9)
		temp_up = create_vector(0, 1, 0);
	else
		temp_up = create_vector(1, 0, 0);
	right = vector_cross_prod(cameradir, temp_up);
	right = normalize(right, 1);
	up = vector_cross_prod(right, cameradir);
	free(temp_up);
	free(right);
	free(cameradir);
	return (up);
}

static void	prepare_n_render(t_object **o, t_parse *parse, t_world *world)
{
	t_camera	*camera;
	float		*cameraup;
	t_matrix	*tmp;
	int			i;

	i = -1;
	while (++i < parse->total)
	{
		o[i]->transform = create_transform(o[i]->transform, o[i]);
		if (o[i]->material->pattern == TRUE)
		{
			free(o[i]->material->color);
			o[i]->material->patt = create_pattern(color(0, 0, 0),
					color(1, 1, 1), create_identity(4));
		}
	}
	camera = create_camera(150, 100, parse->fow * 0.01745329);
	clean_matrix(camera->transform, 4);
	cameraup = compute_up(parse->normv);
	tmp = view_transform(create_point(parse->camc[0], parse->camc[1],
				parse->camc[2]), create_point(parse->normv[0], parse->normv[1],
				parse->normv[2]), cameraup);
	camera->transform = inverse_matrix(tmp);
	clean_matrix(tmp, 4);
	start_display(camera, world);
}

int	main(int argc, char **argv)
{
	t_parse		*parse;
	t_object	**objects;
	t_world		*world;

	if (argc != 2)
	{
		ft_printf(2, "Error\nPlease input one and only one file\n");
		exit (1);
	}
	parse = init_parse();
	objects = check_file(argv[1], parse, FALSE);
	check_extras(objects, parse);
	world = create_world(parse->total, parse->light);
	world->objects = objects;
	prepare_n_render(objects, parse, world);
	clean_parse(parse);
	clean_world(world);
	return (0);
}
