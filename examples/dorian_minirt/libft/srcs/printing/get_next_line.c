/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:22:58 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 10:05:49 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_clear_tmp(char *buf, char *tmp_buf)
{
	char	*tmp;

	tmp = ft_strjoin(buf, tmp_buf);
	free (buf);
	return (tmp);
}

static char	*ft_fill_buffer(int fd, char *buf)
{
	char	*tmp_buf;
	long	bytes;

	if (!buf)
		buf = ft_calloc(1, 1);
	bytes = 1;
	tmp_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (bytes > 0)
	{
		bytes = read(fd, tmp_buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		tmp_buf[bytes] = '\0';
		buf = ft_clear_tmp(buf, tmp_buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(tmp_buf);
	return (buf);
}

static char	*ft_get_line(char *buf)
{
	long	i;
	char	*line;

	i = 0;
	if (!buf[0])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = ft_calloc(i + 1 + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_prep_buffer(char *buf)
{
	long	i;
	long	j;
	char	*tmp;

	if (!buf)
		return (NULL);
	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	tmp = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	i++;
	while (buf[i])
		tmp[j++] = buf[i++];
	free(buf);
	return (tmp);
}

char	*get_next_line(int fd, int clear)
{
	static char	*buf[1000];
	char		*cur_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, buf, 0) && !clear))
		return (NULL);
	if (clear)
	{
		ft_bzero(buf[fd], sizeof(char) * ft_strlen(buf[fd]));
		ft_printf("%s\n", buf[fd]);
		return (NULL);
	}
	buf[fd] = ft_fill_buffer(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	cur_line = ft_get_line(buf[fd]);
	buf[fd] = ft_prep_buffer(buf[fd]);
	return (cur_line);
}
