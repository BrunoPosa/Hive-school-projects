/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:26:25 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 18:29:44 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

void	free_pars(t_rt *rt)
{
	free(rt->sp);
	free(rt->pl);
	free(rt->cy);
}

void	free_all(t_rt *rt)
{
	free_pars(rt);
	mlx_terminate(rt->mlx);
}
