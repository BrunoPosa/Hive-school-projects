/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:53 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 13:55:37 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "errors.h"

/* utils.c */
int		doublelen(char **str);
int		numofel(char **str, int n);
void	free_arr(char **str);
int		is_float(char *str);
float	ft_atof(char *str);

/* utils1.c */
int		is_ulong(char *str);
int		is_color(char **str);

#endif