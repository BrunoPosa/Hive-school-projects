/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_colours.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:42:35 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 23:48:18 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_colour	*add_colours(t_colour *a, t_colour *b)
{
	t_colour	*p;

	p = malloc(sizeof(t_colour));
	if (!a || !b || !p)
		return (NULL);
	p->r = a->r + b-> r;
	p->g = a->g + b-> g;
	p->b = a->b + b-> b;
	return (p);
}

t_colour	*subtract_colours(t_colour *a, t_colour *b)
{
	t_colour	*p;

	p = malloc(sizeof(t_colour));
	if (!a || !b || !p)
		return (NULL);
	//the commented was just a test, but it seems not to be needed
	p->r = a->r - b-> r;// fmax(EPSILON, a->r - b-> r);
	p->g = a->g - b-> g; //fmax(EPSILON, a->g - b-> g);
	p->b = a->b - b-> b;//fmax(EPSILON, a->b - b-> b);
	return (p);
}

t_colour	*multiply_colour_by(t_colour *a, float scaler)
{
	t_colour	*p;

	p = NULL;
	p = malloc(sizeof(t_colour));
	if (!a || !p)
		return (NULL);
	p->r = a->r * scaler;
	p->g = a->g * scaler;
	p->b = a->b * scaler;
	return (p);
}

t_colour	*hadamard_product(t_colour *a, t_colour *b)
{
	t_colour	*p;

	p = malloc(sizeof(t_colour));
	if (!a || !b || !p)
		return (NULL);
	p->r = clamp((a->r * b->r) / 255.0);
	p->g = clamp((a->g * b->g) / 255.0);
	p->b = clamp((a->b * b->b) / 255.0);
	return (p);
}
