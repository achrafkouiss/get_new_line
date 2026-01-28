/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:44:00 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/30 07:57:00 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read(int fd, char *rest)
{
	char	*buffer;
	int		len;

	if (!rest)
	{
		rest = ft_calloc(1, 1);
		if (!rest)
			return (NULL);
	}
	buffer = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(rest), NULL);
	len = 1;
	while (!ft_strchr(buffer, '\n') && len > 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
			return (free(buffer), free(rest), NULL);
		buffer[len] = '\0';
		rest = ft_strjoin(rest, buffer);
		if (!rest)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (rest);
}

static char	*ft_line(char *buffer)
{
	char	*new_line;
	char	*line;
	size_t	len;
	size_t	i;

	if (buffer && buffer[0] == '\0')
		return (NULL);
	new_line = ft_strchr(buffer, '\n');
	if (!new_line)
	{
		line = ft_strdup(buffer);
		return (line);
	}
	len = (new_line - &buffer[0]) + 1;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_rest(char *buffer)
{
	char	*new_buffer;
	char	*new_line;

	new_line = ft_strchr(buffer, '\n');
	if (!new_line)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(new_line + 1);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
	{
		free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_rest(buffer[fd]);
	return (line);
}
