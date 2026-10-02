/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:10 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/18 11:11:36 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_single_player(t_map *map)
{
	int		y;
	int		x;
	int		count;
	char	c;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map->data->player.x = x;
				map->data->player.y = y;
				map->data->player.pov = c;
				count++;
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}

static int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	refuse_tabs(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '\t')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_valid_characters(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!is_valid_map_char(map->grid[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!map || !map->grid || !map->data)
		return (0);
	if (!refuse_tabs(map))
		return (error_msg("Tab character in map"));
	if (!check_valid_characters(map))
		return (error_msg("Invalid character in map"));
	if (!check_single_player(map))
		return (error_msg("Map must have exactly one player"));
	if (!normalize_map_lines(map, 0))
		return (error_msg("Can't normalize map"));
	if (!is_map_closed(map))
		return (error_msg("Map invalid"));
	return (1);
}
