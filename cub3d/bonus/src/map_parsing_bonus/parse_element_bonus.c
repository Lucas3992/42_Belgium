/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:33 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:34 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*extract_path(char *line)
{
	int		i;
	int		start;

	i = 0;
	while (line[i] && !is_space(line[i]))
		i++;
	while (line[i] && is_space(line[i]))
		i++;
	start = i;
	while (line[i] && !is_space(line[i]) && line[i] != '\n')
		i++;
	if (i == start)
		return (NULL);
	return (ft_substr(line, start, i - start));
}

static int	parse_texture(char *line, char **dest)
{
	char	*path;

	path = extract_path(line);
	if (!path)
		return (1);
	if (!is_valid_xpm(path))
		return (free(path), 1);
	*dest = path;
	return (0);
}

static int	parse_color(char *line, t_color *color)
{
	int		i;

	i = 0;
	while (line[i] && !is_space(line[i]))
		i++;
	while (line[i] && is_space(line[i]))
		i++;
	return (parse_rgb(line + i, color));
}

int	parse_element(t_map_config *data, char *line, int index)
{
	if (index == 0)
		return (parse_texture(line, &data->textures.north));
	if (index == 1)
		return (parse_texture(line, &data->textures.south));
	if (index == 2)
		return (parse_texture(line, &data->textures.west));
	if (index == 3)
		return (parse_texture(line, &data->textures.east));
	if (index == 4)
		return (parse_color(line, &data->textures.floor));
	if (index == 5)
		return (parse_color(line, &data->textures.ceiling));
	if (index == 6)
		return (parse_texture(line, &data->textures.enemy));
	return (1);
}
