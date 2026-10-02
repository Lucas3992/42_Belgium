/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_valid_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:01:27 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/01 10:08:55 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	handle_space_line(char *line, int *map_started)
{
	if (*map_started == 0)
	{
		free(line);
		return (0);
	}
	free(line);
	return (-1);
}

static int	process_line(char **line_ptr, int *map_started)
{
	char	*line;
	int		i;

	line = *line_ptr;
	if (ft_isspace(line))
		return (handle_space_line(line, map_started));
	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (is_map_char(line[i]))
	{
		*map_started = 1;
		remove_newline(line);
		return (1);
	}
	if (*map_started == 0)
	{
		free(line);
		return (0);
	}
	free(line);
	return (-1);
}

char	*read_valid_line(int fd, int *map_started)
{
	char	*line;
	int		res;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		res = process_line(&line, map_started);
		if (res == 1)
			return (line);
		if (res < 0)
			return (NULL);
	}
}
