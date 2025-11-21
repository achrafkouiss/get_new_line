/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   please.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:42:27 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/21 09:04:13 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	s_size;
	char	*new_arr;

	s_size = ft_strlen(s) + 1;
	new_arr = malloc(sizeof(char) * s_size);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_arr[i] = s[i];
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	arr_size;
	char	*new_arr;
	size_t	i;

	if (!nmemb || !size)
		return (malloc(0));
	if ((size_t)-1 / size < nmemb)
		return (NULL);
	arr_size = size * nmemb;
	new_arr = malloc(arr_size);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < arr_size)
		new_arr[i++] = 0;
	return (new_arr);
}

char	*ft_strchr(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if ((char)c == '\0')
		return (str);
	return (NULL);
}

char	*ft_fill_str(char *str, char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[len + i] = s2[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_arr;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_arr = malloc(s1_len + s2_len + 1);
	if (!new_arr)
		return (NULL);
	new_arr = ft_fill_str(new_arr, s1, s2, s1_len);
	return (new_arr);
}

char	*ft_read_line(int fd, char *rest, int *len)
{
	char	*buffer;
	char	*tmp;

	if (!rest)
		rest = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(rest), NULL);
	*len = 1;
	while (*len > 0)
	{
		*len = read(fd, buffer, BUFFER_SIZE);
		if (*len == -1)
			return (free(buffer), NULL);
		buffer[*len] = '\0';
		tmp = rest;
		rest = ft_strjoin(rest, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), rest);
}

char	*ft_allo_line(char *buffer)
{
	char	*line;
	int		size;
	int		i;
	char	*nl;

	nl = ft_strchr(buffer, '\n');
	if (!nl)
		return (ft_strdup(buffer));
	size = (nl - buffer) + 2;
	line = ft_calloc(size, sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < size - 1)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_allo_rest(char *rest)
{
	char	*nl;
	char	*new_rest;

	nl = ft_strchr(rest, '\n');
	if (!nl)
	{
		free(rest);
		return (NULL);
	}
	nl++;
	new_rest = ft_strdup(nl);
	free(rest);
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			len;

	buffer = ft_read_line(fd, buffer, &len);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_allo_line(buffer);
	buffer = ft_allo_rest(buffer);
	return (line);
}

int	main(void)
{
	char *str;
	int fd = open("text", O_RDONLY);

	if (fd == -1)
		return (-1);
	int i = 0;
	while ((str = get_next_line(fd)) != NULL && i < 10)
	{
		printf("%s", str);
		free(str);
		i++;
	}
    free(str);
}