/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:28:06 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 04:02:23 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

char	*skip_space(char *s)
{
	if (!s)
		return (NULL);
	while (*s && *s == ' ')
		s++;
	return (s);
}

int	does_file_end_with_rt(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (ft_strncmp(&filename[len - 3], ".rt", 3))
		return (0);
	return (1);
}

float	calculate_focal_len(unsigned int fov)
{
	float	fov_radians;
	float	focal_len;

	fov_radians = (fov * M_PI) / 180.0;
	focal_len = 1 / tan(fov_radians / 2.0);
	return (focal_len);
}

t_rgb	black(void)
{
	return (create_colour(0, 0, 0));
}
