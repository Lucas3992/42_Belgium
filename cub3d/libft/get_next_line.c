/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 06:45:12 by sleyro            #+#    #+#             */
/*   Updated: 2025/11/21 14:15:09 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cleanfree_gnl(char **toclean)
{
	if (*toclean)
	{
		free(*toclean);
		*toclean = NULL;
	}
	return (NULL);
}

static char	*keep_stash(char *line)
{
	int		i;
	char	*remains;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == 0 || line[i + 1] == 0)
		return (NULL);
	remains = ft_substr_gnl(line, i + 1, ft_strlen_gnl(line) - (i + 1));
	if (!remains || *remains == 0)
		return (cleanfree_gnl(&remains));
	line[i + 1] = 0;
	return (remains);
}

static char	*build_stash(int fd, char *stash, char *bufferstr)
{
	int		isread;
	char	*tempstr;

	isread = 1;
	while (isread > 0)
	{
		isread = read(fd, bufferstr, BUFFER_SIZE);
		if (isread == -1)
			return (cleanfree_gnl(&stash));
		else if (isread == 0)
			break ;
		bufferstr[isread] = '\0';
		if (!stash)
			stash = ft_strdup_gnl("");
		tempstr = stash;
		stash = ft_join_gnl(tempstr, bufferstr, isread);
		free(tempstr);
		if (!stash)
			return (cleanfree_gnl(&stash));
		if (ft_strchr2(bufferstr, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (cleanfree_gnl(&stash));
	line = build_stash(fd, stash, buffer);
	if (!line)
		return (cleanfree_gnl(&stash));
	stash = keep_stash(line);
	return (line);
}
