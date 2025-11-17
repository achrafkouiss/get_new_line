/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 08:17:29 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/17 20:46:25 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

static char	*s;
static char	*flash;
static int	buffer;

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if ((char)c == '\0')
		return (s);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*pointer;
	size_t			i;

	if (!s)
		return ;
	i = 0;
	pointer = (unsigned char *)s;
	while (i < n)
	{
		pointer[i] = 0;
		i++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	// printf("src = %s\n", src);
	if (!dest || !src)
		return (NULL);
	while (src[i])
	{
		// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		dest[i] = src[i];
		i++;
	}
	// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	dest[i] = '\0';
	return (dest);
}

char	*ft_allo(void)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	buffer += BUFFER_SIZE;
	i = 0;
	len = buffer - BUFFER_SIZE;
	str = malloc(buffer + 1);
	ft_bzero(str, BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	// printf("s = %s\n", s);
	// if (buffer == 42)
	// {
	// 	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	//     ft_strcpy(str, s);
	// 	printf("str = %s\n", str);
	// 	free(s);
	// 	free(flash);
	// 	return (str);
	// }
	// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	ft_strcpy(str, flash);
	while (s[i])
	{
		// printf("str[%d] = %c\n", len + i, str[len + i]);
		// printf("s[%d] = %c\n", len + i, s[i]);
		str[len + i] = s[i];
		// printf("str[%d] = %c\n", len + i, str[len + i]);
		// printf("s[%d] = %c\n", len + i, s[i]);
		i++;
	}
	str[len + i] = '\0';
	// printf("str[%d] = %d\n", len + i, str[len + i]);
	// for (j = 0; j < buffer + 1; j++)
	// 	printf("str[%d] = %d\n", j, str[j]);
	return (str);
}

char	*get_next_line(int fd)
{
	int	len;
	int	index;

	s = malloc(BUFFER_SIZE + 1);
	ft_bzero(s, BUFFER_SIZE + 1);
	if (!s)
		return (NULL);
	len = read(fd, s, BUFFER_SIZE);
	// printf("len = %d\n", len);
	if (len == 0 || len == -1)
	{
		// printf("flash = %s\n", flash);
		return (NULL);
	}
	// printf("s = %s\n", s);
	// if (!ft_strchr(s, '\n') && i == 0)
	// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	while (!ft_strchr(s, '\n') && (BUFFER_SIZE >= len && len > 0))
	{
		// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		flash = ft_allo();
		len = read(fd, s, BUFFER_SIZE);
		printf("len = %d\n", len);
		if (BUFFER_SIZE > len && len > 0)
		{
			flash = ft_allo();
			return (flash);
		}
		//  printf("flash = %s\n", flash);
	}
	// if (len == 0 || len == -1)
	// 	return (NULL);
	// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	return (flash);
}

int	main(void)
{
	char *str;
	int fd = open("text", O_RDONLY);

	if (fd == -1)
		return (-1);
	// printf("%d\n", fd);
	// str = get_next_line(fd);
	// ft_putstr(str);
	// str = get_next_line(fd);
	// ft_putstr(str);
	// str = get_next_line(fd);
	// ft_putstr(str);
	while ((str = get_next_line(fd)) != NULL)
	{
		// printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		ft_putstr(str);
		free(str);
	}
}