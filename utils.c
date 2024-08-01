/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:27 by bposa             #+#    #+#             */
/*   Updated: 2024/07/31 20:24:28 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(char *n)
{
	int	res;

	res = 0;
	while (n && *n >= '0' && *n <= '9')
		res = res * 10 + *n++ - '0';
	return (res);
}

long long int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return(ERROR);
	return ((long long int)(time.tv_sec * 1000LL + time.tv_usec / 1000));//(time.tv_usec + 500) / 1000??
}

int	wait_ms(long long int mseconds, t_philo *p)
{
	long long int	start;
	long long int	current;

	current = 0;
	start = get_time_ms();
	while (!*p->dead && current - start < mseconds)
	{
		current = get_time_ms();
		usleep(400);
	}
	return (SUCCESS);
}

int	my_strncmp(const char *s1, const char *s2, size_t n)
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
