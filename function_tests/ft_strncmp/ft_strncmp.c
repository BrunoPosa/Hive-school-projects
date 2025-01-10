/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:08:50 by bposa             #+#    #+#             */
/*   Updated: 2024/11/02 10:59:07 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i + 1 < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


#include<stdio.h>
int	main(void)
{
	char *s1="sp    31,321,3";
	char *s2="sp";
	char *s3="t";
	char *s4="st";
	int i = 0;

	i = ft_strncmp(s1, s2, 1);
	printf("same test = i = %d\n", i);
	i = ft_strncmp(s1, s3, 1);
	printf("diff test = i = %d\n", i);
	i = ft_strncmp(s4, s1, 1);
	printf("l1 test = i = %d\n", i);
	i = ft_strncmp(s4, s1, 2);
	printf("l2 test = i = %d\n", i);
}

