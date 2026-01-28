/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouiss <akouiss@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:52:46 by akouiss           #+#    #+#             */
/*   Updated: 2025/11/30 07:57:05 by akouiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*ft_strchr(char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char *s1, char *s2);

#endif
