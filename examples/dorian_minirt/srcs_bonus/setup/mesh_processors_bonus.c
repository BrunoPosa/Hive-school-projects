/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_processors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:27:05 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/26 17:08:19 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minirt_bonus.h"
#include	"objects_bonus.h"
#include	"libft_bonus.h"
#include	"scene_bonus.h"

char	*process_vertex(t_mesh *mesh, char *line, int fd)
{
	int		count;

	count = 0;
	while (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ')
	{
		mesh->vertex[count] = get_vec3_mesh(line + 1);
		count++;
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	return (line);
}

char	*process_normals(t_mesh *mesh, char *line, int fd)
{
	int		count;

	count = 0;
	while (!ft_empty_str(line) && !ft_strncmp("vn", line, 2)
		&& line[2] == ' ' && line)
	{
		mesh->normals[count] = get_vec3_mesh(line + 2);
		count++;
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	return (line);
}

char	*process_faces(t_mesh *mesh, char *line, int fd)
{
	int		count;

	count = 0;
	while (!ft_empty_str(line) && !ft_strncmp("f", line, 1)
		&& line[1] == ' ' && line)
	{
		get_faces(line + 1, mesh->faces[count], mesh);
		count++;
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	return (line);
}

char	*process_textures(t_mesh *mesh, char *line, int fd)
{
	int		count;

	count = 0;
	while (!ft_empty_str(line) && !ft_strncmp("vt", line, 2) && line[2] == ' '
		&& line && mesh->count_vt != 0)
	{
		mesh->textures[count] = get_textures(line + 2);
		count++;
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	return (line);
}
