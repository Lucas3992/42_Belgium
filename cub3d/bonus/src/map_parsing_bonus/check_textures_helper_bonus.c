/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_helper_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:42 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:43 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_cardinal(char *line, char *expected)
{
	int	len;

	if (!line || !expected)
		return (0);
	len = ft_strlen(expected);
	if (ft_strncmp(line, expected, len) != 0)
		return (0);
	if (!is_space(line[len]) && line[len] != '\0')
		return (0);
	return (1);
}

int	check_txt_order(int fd)
{
	static char	*cardinal[7] = {"NO", "SO", "WE", "EA", "F", "C", "M"};
	char		*line;
	int			i;

	if (fd < 0)
		return (1);
	i = 0;
	while (i < 7)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (ft_isspace(line))
		{
			free(line);
			continue ;
		}
		if (!check_cardinal(line, cardinal[i]))
			return (free(line), 1);
		free(line);
		i++;
	}
	return (0);
}

int	is_valid_xpm(char *path)
{
	int	len;
	int	fd;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	rgb_to_argb(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
