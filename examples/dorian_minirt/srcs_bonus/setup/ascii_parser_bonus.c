/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:29 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/26 21:51:55 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minirt_bonus.h"
#include	"objects_bonus.h"
#include	"libft_bonus.h"
#include	"scene_bonus.h"

static void	init_arrays(t_mesh *mesh, int fd)
{
	char	*line;

	line = get_next_line(fd, FALSE);
	while (line)
	{
		line = process_vertex(mesh, line, fd);
		line = process_normals(mesh, line, fd);
		line = process_faces(mesh, line, fd);
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	if (line)
		free(line);
	if (close(fd) < 0)
		ft_error(errno);
}

void	ascii_parser(t_mesh *mesh, char *line)
{
	int		fd;
	char	**file_name;
	int		index;

	line += 3;
	mesh->type = mesh_obj;
	mesh->obj_id = -1;
	file_name = ft_split2(line);
	fd = open(file_name[0], O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	count_file_objects(fd, mesh);
	allocate_arrays(mesh);
	fd = open(file_name[0], O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	init_arrays(mesh, fd);
	index = 0;
	while (index < mesh->count_vn)
		index++;
	close(fd);
	create_mesh(mesh);
	ft_free_array(&file_name, ft_count_elements(file_name));
}
