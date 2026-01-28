/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:44:30 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/30 07:47:51 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	s_size;
	char	*new_arr;

	if (!*s)
		return (NULL);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}
