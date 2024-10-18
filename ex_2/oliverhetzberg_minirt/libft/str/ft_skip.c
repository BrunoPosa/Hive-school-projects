/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:20:26 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 16:20:27 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/* making new string that will skip first and last character in our old
string and change it in memory */
void	ft_skip_fl(char **str)
{
	char	*new_str;
	char	*original_str;
	int		i;
	int		j;

	new_str = (char *)malloc(ft_strlen(*str) - 1);
	if (!new_str)
		exit(1);
	original_str = *str;
	i = 0;
	j = 1;
	while (original_str[j + 1] != '\0' && (size_t)i < ft_strlen(*str))
	{
		new_str[i] = original_str[j];
		j++;
		i++;
	}
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
}
