/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:30:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/29 12:30:04 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(int error)
{
	static const	char	(*errors[]) = {
		"File extension must be .rt\n",
		"Input format invalid. Consult the subject for format specifications.\n",
		"Numerical value out of range\n",
		"Identifier not recognised.\n",
		"Scene must have only one camera and ambient light.\n",
		"Scene must have one camera.\n",
	};

	ft_printf_fd(STDERR_FILENO, "\e[2;31mError\x1b[m:\n");
	if (error < 160)
		ft_printf_fd(STDERR_FILENO, "%s\n", strerror(error));
	else
		ft_printf_fd(STDERR_FILENO, "%s\n", errors[error - 160]);
	exit(error);
}

void	check_line(char **line)
{
	ft_skip_ws(line);
	ft_skip_num(line, INT, 0);
	ft_skip_ws(line);
	if (**line != '\n' && **line != '\0')
		ft_error(input_err);
}

static float	offset_light(int *state)
{
	int			x;
	float		new_x;

	x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	new_x = ft_frac(x / 316741.234234f) * 0.01f;
	*state = x;
	return (new_x);
}

void	validate_scene(t_scene *scene)
{
	int			num;
	static int	state;

	num = 0;
	state = 4756345;
	while (num < scene->n_lights && scene->lights[num].valid)
	{
		scene->lights[num].pos.x += offset_light(&state);
		scene->lights[num].pos.y += offset_light(&state);
		scene->lights[num].pos.z += offset_light(&state);
		if (scene->n_lights != 1)
			ft_error(content_err);
		num++;
	}
	if (scene->cam.valid != 1)
		ft_error(content_err);
	if (scene->amb.valid != 1)
		ft_error(content_err);
}
