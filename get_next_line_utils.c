/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:05:15 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/21 18:23:23 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
