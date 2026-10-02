/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:28 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:29 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_cub(char *map_name)
{
	int		len;
	char	*ext;

	len = ft_strlen(map_name);
	if (len < 4)
		return (1);
	ext = ft_substr(map_name, len - 4, 4);
	if (!ext)
		return (1);
	if (ft_strncmp(".cub", ext, 4))
	{
		free(ext);
		printf("Error\nNo .cub file found.\n");
		return (1);
	}
	free(ext);
	return (0);
}

int	read_map(char *map_path, t_map_config *map_data)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (get_textures(fd, map_data))
	{
		printf("Error\nUnable to get textures\n");
		return (close(fd), 1);
	}
	if (get_map(fd, &map_data->map, map_data))
	{
		printf("Error\nUnable to get map\n");
		return (close(fd), 1);
	}
	close(fd);
	return (0);
}

static int	validate_and_parse_line(char *line, char *expected,
	t_map_config *data, int i)
{
	int	len;

	len = ft_strlen(expected);
	if (ft_strncmp(line, expected, len) != 0 || !is_space(line[len]))
		return (1);
	if (parse_element(data, line, i) != 0)
		return (1);
	return (0);
}

static int	read_texture_line(int fd, char *expected, t_map_config *data, int i)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	if (!line)
		return (1);
	if (ft_isspace(line))
	{
		free(line);
		return (0);
	}
	ret = validate_and_parse_line(line, expected, data, i);
	free(line);
	if (ret != 0)
		return (1);
	return (2);
}

int	get_textures(int fd, t_map_config *data)
{
	char	*cardinal[7];
	int		i;
	int		ret;

	fill_cardinal(cardinal);
	i = 0;
	while (i < 7)
	{
		ret = read_texture_line(fd, cardinal[i], data, i);
		if (ret == 1)
			return (1);
		if (ret == 2)
			i++;
	}
	return (0);
}
