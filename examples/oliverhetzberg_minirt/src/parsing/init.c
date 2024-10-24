/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:05:19 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 14:07:40 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

void	init_vector(t_vec *v)
{
	v->x = 0.0;
	v->y = 0.0;
	v->z = 0.0;
}

void	init_amb(t_rt *rt)
{
	rt->a.id = 0;
	rt->a.ratio = 0;
	init_vector(&rt->a.col);
}

void	init_camera(t_rt *rt)
{
	rt->c.id = 0;
	init_vector(&rt->c.point);
	init_vector(&rt->c.or_vec);
	rt->c.fov = 0.0;
}

/*
count how many sp, pl and cy are in file and add it to the struct
*/
static void	count_str(t_rt *rt, t_index *j, int fd)
{
	char	*str;

	init_index(j);
	str = get_next_line(fd);
	while (str != NULL)
	{
		ft_num_of_sub(str, "sp", &j->s);
		ft_num_of_sub(str, "pl", &j->p);
		ft_num_of_sub(str, "cy", &j->c);
		free(str);
		str = get_next_line(fd);
	}
	rt->num_sp = j->s;
	rt->num_pl = j->p;
	rt->num_cy = j->c;
	init_index(j);
}

void	init_rt(t_rt *rt, t_index *j, char **argv)
{
	int	fd;

	rt->width = WIDTH;
	rt->height = HEIGHT;
	fd = open_file(argv[1]);
	count_str(rt, j, fd);
	close(fd);
	init_amb(rt);
	init_camera(rt);
	init_light(rt);
	init_sphere(rt);
	init_plane(rt);
	init_cylinder(rt);
}
