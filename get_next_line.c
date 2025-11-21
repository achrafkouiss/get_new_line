/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:42:27 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/21 22:31:34 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *buffer)
{
	char	*line;
	char	*nl;
	int		len;
	int		i;

	if (!buffer || !buffer[0])
		return (NULL);
	nl = ft_strchr(buffer, '\n');
	if (nl)
		len = (nl - buffer) + 1;
	else
		len = ft_strlen(buffer);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*remove_line(char *buffer)
{
	char	*nl;
	char	*rest;

	nl = ft_strchr(buffer, '\n');
	if (!nl)
	{
		free(buffer);
		return (NULL);
	}
	rest = ft_strdup(nl + 1);
	free(buffer);
	return (rest);
}

static char	*read_fd(int fd, char *buffer)
{
	char	*tmp;
	char	*buf;
	int		len;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	len = 1;
	while (!ft_strchr(buffer, '\n') && len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
			return (free(buf), free(buffer), NULL);
		buf[len] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(tmp, buf);
	}
	free(buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = remove_line(buffer);
	return (line);
}
#include <stdio.h>
int	main(void)
{
	char *str;
	int fd = open("text", O_RDWR);

	if (fd == -1)
		return (-1);
	str = get_next_line(fd);
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);
	// while ((str = get_next_line(fd)) != NULL && i < 10)
	// {
	// 	printf("%s", str);
	// 	free(str);
	// 	i++;
	// }
    free(str);
}