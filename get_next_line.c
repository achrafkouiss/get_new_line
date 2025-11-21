/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:42:27 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/21 20:53:15 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if(!rest)
		free(rest);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	*len = 1;
	while (*len > 0)
	{
		*len = read(fd, buffer, BUFFER_SIZE);
		if (*len == -1)
			return (free(buffer), NULL);
		// if (*len == 0)
		// 	return (free(buffer), rest);
		buffer[*len] = '\0';
		tmp = rest;
		rest = ft_strjoin(rest, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), rest);
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

	if (fd < 0 || BUFFER_SIZE < 0)
		return(NULL);
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
// #include <stdio.h>
// int	main(void)
// {
// 	char *str;
// 	int fd = open("text", O_RDWR);

// 	if (fd == -1)
// 		return (-1);
// 	str = get_next_line(fd);
// 	printf("%s", str);
// 	str = get_next_line(fd);
// 	printf("%s", str);
// 	// while ((str = get_next_line(fd)) != NULL && i < 10)
// 	// {
// 	// 	printf("%s", str);
// 	// 	free(str);
// 	// 	i++;
// 	// }
//     free(str);
// }