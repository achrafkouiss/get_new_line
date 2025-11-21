/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:06:24 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/21 18:39:07 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#elif BUFFER_SIZE < 0
# undef BUFFER_SIZE
# define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*ft_allo_rest(char *rest);
char	*ft_read_line(int fd, char *rest, int *len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_fill_str(char *str, char *s1, char *s2, int len);
char	*ft_allo_line(char *buffer);
char	*ft_strchr(char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *str);

#endif
