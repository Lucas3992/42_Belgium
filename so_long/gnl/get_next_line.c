/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:04:18 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/22 09:34:09 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*easy_free(char *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

static char	*buf_to_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE +1];
	char	*tmp;
	int		i;

	if (!stash)
		stash = ft_strdup("");
	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buffer[i] = '\0';
		tmp = ft_strjoin(stash, buffer, i);
		if (!tmp)
			return (easy_free(stash));
		stash = easy_free(stash);
		stash = tmp;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	if (i < 0 || (i == 0 && (!stash || *stash == '\0')))
		return (easy_free(stash));
	return (stash);
}

static char	*extrct_before_newline(char *stash)
{
	int	i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static char	*extract_after_newline(char *stash)
{
	int		i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (NULL);
	return (ft_substr(stash, i +1, ft_strlen(stash) - (i +1)));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*new_stash;

	if (fd == -19)
		easy_free(stash);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = buf_to_stash(fd, stash);
	if (!stash || *stash == '\0')
		return (NULL);
	if (!ft_strchr(stash, '\n') && *stash)
	{
		line = ft_strdup(stash);
		stash = easy_free(stash);
		return (line);
	}
	line = extrct_before_newline(stash);
	new_stash = extract_after_newline(stash);
	stash = easy_free(stash);
	stash = new_stash;
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int main ()
{
	int fd = open("fichier_avec_n.txt", O_RDONLY);
	char *line;
	
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		line = easy_free(line);
	}
	close(fd);
	printf("%c", '\n');
	printf("%c", '\n');

	fd = open("fichier_sans_n.txt", O_RDONLY);
	
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		line = easy_free(line);
	}
	close(fd);
	printf("%c", '\n');
	printf("%c", '\n');
	
	fd = open("fichier_vide.txt", O_RDONLY);
	
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		line = easy_free(line);
	}
	close(fd);
	printf("%c", '\n');
	printf("%c", '\n');
	return (0);
}
*/