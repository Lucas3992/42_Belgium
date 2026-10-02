/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:04:28 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/05/15 09:08:01 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# elif BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2, int size_buf);
char	*ft_strchr(const char	*s, int c);
size_t	ft_strlen(const char	*s);

#endif