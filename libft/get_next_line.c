/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/24 23:06:47 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*my_mmov(void *dst, void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	if (src < dst)
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
		return (dst);
	}
	else
	{
		while (len > 0)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
			len--;
		}
	}
	return (dst);
}

static char	*my_strjoin(char *rvalue1, char *buffer1, size_t buffer_len)
{
	char	*joined;
	size_t	rvalue1_len;

	if (rvalue1)
		rvalue1_len = my_strlen(rvalue1);
	else
		rvalue1_len = 0;
	joined = ft_calloc(rvalue1_len + buffer_len + 1, sizeof(char));
	if (!joined)
	{
		if (rvalue1)
		{
			free(rvalue1);
			rvalue1 = NULL;
		}
		return (NULL);
	}
	joined[rvalue1_len + buffer_len] = 0;
	my_memcpy(joined, rvalue1, rvalue1_len + 1);
	my_memcpy(joined + rvalue1_len, buffer1, buffer_len + 1);
	if (rvalue1)
		free(rvalue1);
	return (joined);
}

static ssize_t	shift_count_setter(char *buffer, int *newline)
{
	ssize_t	i;

	i = 0;
	*newline = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			*newline = 1;
			return (i);
		}
		i++;
	}
	return (i);
}

static int	buffer_handler(char *buffer, char **rvalue, int *error)
{
	ssize_t	shift_count;
	int		newline;

	newline = 0;
	if (*buffer == 0)
		return (0);
	shift_count = shift_count_setter(buffer, &newline);
	*rvalue = my_strjoin(*rvalue, buffer, shift_count + newline);
	if (*rvalue == NULL)
		return (*error = -1);
	my_mmov(buffer, &buffer[shift_count + newline], BUFFER_SIZE - shift_count);
	my_bzero(&buffer[BUFFER_SIZE - shift_count]);
	return (newline);
}

/*
*	*error is -1 on error, or >=0 when a line is successfuly read.
*	Returns string containing next line, or NULL on error/EOF.
*/
char	*get_next_line(int fd, int *error)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*rvalue;

	rvalue = NULL;
	*error = 42;
	while (*error != 0 && *error != -1)
	{
		if (buffer_handler(buffer, &rvalue, error) == 1)
			return (rvalue);
		if (*error == -1)
		{
			if (rvalue)
				free(rvalue);
			my_bzero(buffer);
			return (NULL);
		}
		*error = read(fd, buffer, BUFFER_SIZE);
	}
	if (*error == -1 && rvalue)
		return (free(rvalue), NULL);
	if (rvalue == NULL && (*error == 0 || *error == -1))
		return (NULL);
	return (rvalue);
}
