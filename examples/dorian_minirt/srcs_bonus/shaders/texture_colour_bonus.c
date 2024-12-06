/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colour_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:55:38 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 18:41:39 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "minirt_bonus.h"
#include "patterns_bonus.h"

t_vec3	get_texture_norm(t_texture *texture, t_vec2 uv)
{
	t_vec3	normal;
	t_vec2	pxl;

	pxl.x = uv.x * (texture->picture.width - 1);
	pxl.y = uv.y * (texture->picture.height - 1);
	normal = texture->picture.norm_vecs[(int)pxl.y
		* texture->picture.width + (int)pxl.x];
	return (normal);
}

t_vec4	get_texture_col(t_texture *texture, t_vec2 uv)
{
	int		*dst;
	t_vec4	colour;
	t_vec2	pxl;

	pxl.x = uv.x * (texture->picture.width - 1);
	pxl.y = uv.y * (texture->picture.height - 1);
	dst = (int *)(texture->picture.addr
			+ (int)pxl.y * texture->picture.line_length
			+ (int)pxl.x * (texture->picture.bits_per_pixel / 8));
	colour = ft_int32tov4(*dst);
	ft_rgbtonorm(&colour);
	return (colour);
}

void	get_texture_info(t_object *object, t_vec3 *point,
		t_vec4 *colour, t_vec3 *normal)
{
	static const t_col_func	colour_func[] = {
		get_checkers, get_brick, get_texture_col
	};
	static const t_map_func	map_func[] = {
		spherical_map,
		plane_map,
		cylinder_map,
		disk_map,
		triangle_map,
		cone_map
	};
	t_vec2					uv;

	if (object->type == mesh_obj)
		return ;
	uv = map_func[object->type](point, object);
	if (object->meta.tex_col && object->meta.tex_col->picture.pattern \
		!= normal_pat)
		*colour = colour_func[object->meta.tex_col->picture.pattern - 1] \
		(object->meta.tex_col,
				uv);
	if (object->meta.tex_norm && object->meta.tex_norm->picture.pattern \
		== normal_pat)
		*normal = get_texture_norm(object->meta.tex_norm, uv);
}
