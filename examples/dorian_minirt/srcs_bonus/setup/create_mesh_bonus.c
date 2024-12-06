/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mesh_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:43:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/27 11:31:42 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"
#include "objects_bonus.h"

static void	build_triangles(t_mesh *mesh, int index)
{
	mesh->triangle_data[index].type = triangle_obj;
	mesh->triangle_data[index].triangle.normal = \
	mesh->normals[(mesh->faces[index]->n) - 1];
	mesh->triangle_data[index].triangle.tri_point[0] = \
	mesh->vertex[(mesh->faces[index][0].v) - 1];
	mesh->triangle_data[index].triangle.tri_point[1] = \
	mesh->vertex[(mesh->faces[index][1].v) - 1];
	mesh->triangle_data[index].triangle.tri_point[2] = \
	mesh->vertex[(mesh->faces[index][2].v) - 1];
	mesh->triangle_data[index].triangle.colour = (t_vec4){1, 100, 0, 100};
	mesh->triangle_data[index].triangle.edges[0] = vec3_sub(\
	mesh->triangle_data[index].triangle.tri_point[1],
			mesh->triangle_data[index].triangle.tri_point[0]);
	mesh->triangle_data[index].triangle.edges[1] = vec3_sub(\
	mesh->triangle_data[index].triangle.tri_point[2], \
		mesh->triangle_data[index].triangle.tri_point[0]);
}

void	create_mesh(t_mesh *mesh)
{
	int	index;

	index = 0;
	mesh->n_triangles = mesh->count_f;
	mesh->triangle_data = malloc(mesh->n_triangles * sizeof(t_object));
	while (index < mesh->n_triangles)
	{
		build_triangles(mesh, index);
		index++;
	}
}
