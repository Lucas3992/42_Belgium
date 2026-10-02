/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:45:48 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/01 13:48:51 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*pad_line_with_spaces(char *line, int max_width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (len >= max_width)
		return (ft_strdup(line));
	padded = malloc((max_width + 1) * sizeof(char));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < max_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[max_width] = '\0';
	return (padded);
}

int	normalize_map_lines(t_map *map, int y)
{
	char	**normalized;
	char	*padded;

	normalized = malloc((map->height + 1) * sizeof(char *));
	if (!normalized)
		return (0);
	while (y < map->height)
	{
		padded = pad_line_with_spaces(map->grid[y], map->width);
		if (!padded)
		{
			while (--y >= 0)
				free(normalized[y]);
			free(normalized);
			return (0);
		}
		free(map->grid[y]);
		normalized[y] = padded;
		y++;
	}
	normalized[map->height] = NULL;
	free(map->grid);
	map->grid = normalized;
	return (1);
}
