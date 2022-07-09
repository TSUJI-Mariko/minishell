/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:45:22 by mtsuji            #+#    #+#             */
/*   Updated: 2022/06/06 23:26:28 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int	inside_gnl(char *buf, char **line, int fd, char *cur)
{
	char		*line_cpy;
	long		read_line;
	char		*tmp;

	while (!ft_strchr(cur, '\n'))
	{
		if (*line)
		{
			line_cpy = ft_strjoin(*line, cur);
			free(*line);
			*line = ft_strdup(line_cpy);
			free(line_cpy);
		}
		else
			*line = ft_strdup("");
		read_line = read(fd, buf, BUFFER_SIZE);
		buf[read_line] = '\0';
		cur = buf;
		if (read_line < 0)
			return (-1);
		if (read_line == 0)
			return (0);
	}
	*ft_strchr(cur, '\n') = '\0';
	line_cpy = ft_strdup(*line);
	free(*line);
	*line = ft_strjoin(line_cpy, cur);
	free(line_cpy);
	tmp = ft_strchr(cur, '\0') + 1;
	cur = tmp;
	return (1);
}
*/

int	inside_gnl(char *buf, char **line, int fd, char *cur)
{
	char	*line_cpy;
	long	read_line;

	while (!ft_strchr(cur, '\n'))
	{
		line_cpy = ft_strdup(*line);
		free(*line);
		*line = ft_strjoin(line_cpy, cur);
		free(line_cpy);
		read_line = read(fd, buf, BUFFER_SIZE);
		buf[read_line] = '\0';
		cur = buf;
		if (read_line < 0)
			return (-1);
		if (read_line == 0)
			return (0);
	}
	*ft_strchr(cur, '\n') = '\0';
	line_cpy = ft_strdup(*line);
	free(*line);
	*line = ft_strjoin(line_cpy, cur);
	free(line_cpy);
	cur = ft_strchr(cur, '\0') + 1;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*cur = NULL;
	long		read_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	read_line = 0;
	if (!cur)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line < 0)
			return (-1);
		buf[read_line] = '\0';
		cur = buf;
	}
	*line = ft_strdup("");
	return (inside_gnl(buf, line, fd, cur));
}
