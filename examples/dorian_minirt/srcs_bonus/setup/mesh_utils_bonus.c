/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:20:30 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/27 09:08:21 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minirt_bonus.h"
#include	"objects_bonus.h"
#include	"libft_bonus.h"
#include	"scene_bonus.h"

t_vec3	get_vec3_mesh(char *line)
{
	t_vec3	vec;

	ft_skip_ws(&line);
	vec.x = ft_atof(line);
	ft_skip_num(&line, REAL, 1);
	ft_skip_ws(&line);
	vec.y = ft_atof(line);
	ft_skip_num(&line, REAL, 1);
	ft_skip_ws(&line);
	vec.z = ft_atof(line);
	if (*line == '-')
		line += 1;
	ft_skip_num(&line, REAL, 1);
	return (vec);
}

void	count_file_objects(int fd, t_mesh *mesh)
{
	char	*line;

	line = get_next_line(fd, FALSE);
	while (line)
	{
		if (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ')
			mesh->count_v++;
		else if (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) \
		&& line[2] == ' ')
			mesh->count_vn++;
		else if (!ft_empty_str(line) && !ft_strncmp("vt", line, 1) \
		&& line[2] == ' ')
			mesh->count_vt++;
		else if (!ft_empty_str(line) && !ft_strncmp("f", line, 1) \
		&& line[1] == ' ')
			mesh->count_f++;
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	if (line)
		free(line);
	if (close(fd) < 0)
		ft_error(errno);
}

void	get_faces(char *line, t_vec3_face *key, t_mesh *mesh)
{
	char	**split ;
	int		i;

	i = 0;
	split = ft_split3(line, '/', ' ');
	while (i < 3)
	{
		if (mesh->count_vt != 0)
		{
			key[i].v = ft_atoi(split[i * 3]);
			key[i].t = ft_atoi(split[i * 3 + 1]);
			key[i].n = ft_atoi(split[i * 3 + 2]);
		}
		else
		{
			key[i].v = ft_atoi(split[i * 2]);
			key[i].t = 0;
			key[i].n = ft_atoi(split[i * 2 + 1]);
		}
		i++;
	}
	ft_free_anyarray((void *) &split, ft_count_elements(split));
}

t_vec2	get_textures(char *line)
{
	t_vec2	vec;

	ft_skip_ws(&line);
	vec.x = ft_atof(line);
	ft_skip_num(&line, REAL, 1);
	ft_skip_ws(&line);
	vec.y = ft_atof(line);
	ft_skip_num(&line, REAL, 1);
	ft_skip_ws(&line);
	if (*line == '-')
		line += 1;
	ft_skip_num(&line, REAL, 1);
	return (vec);
}

void	allocate_arrays(t_mesh *mesh)
{
	int		count;

	count = 0;
	mesh->vertex = malloc(mesh->count_v * sizeof(t_vec3));
	mesh->normals = malloc(mesh->count_vn * sizeof(t_vec3));
	if (mesh->count_vt != 0)
		mesh->textures = malloc(mesh->count_vt * sizeof(t_vec2));
	mesh->faces = malloc(mesh->count_f * sizeof(t_vec3_face *));
	while (count < mesh->count_f)
	{
		mesh->faces[count] = malloc(3 * sizeof(t_vec3_face));
		count++;
	}
}
