/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:26 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/18 11:50:28 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	inside_walkable(t_map *og, int y, int x)
{
	if (y == 0 || y == og->height - 1 || x == 0)
		return (0);
	if (x >= (int)ft_strlen(og->grid[y]) - 1)
		return (0);
	if (og->grid[y][x + 1] == ' ')
		return (0);
	if (y > 0 && x >= (int)ft_strlen(og->grid[y - 1]))
		return (0);
	if (y > 0 && og->grid[y - 1][x] == ' ')
		return (0);
	if (y < og->height - 1 && x >= (int)ft_strlen(og->grid[y + 1]))
		return (0);
	if (y < og->height - 1 && og->grid[y + 1][x] == ' ')
		return (0);
	return (1);
}

int	check_edges_are_walls(t_map *og)
{
	int	y;
	int	x;

	y = 0;
	while (y < og->height)
	{
		x = 0;
		while (og->grid[y][x])
		{
			if (is_walkable(og->grid[y][x]))
			{
				if (!inside_walkable(og, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_all_walkable_visited(char **map_copy, t_map *og)
{
	int	y;
	int	x;

	y = 0;
	while (y < og->height)
	{
		if (!og->grid[y])
			return (0);
		x = 0;
		while (og->grid[y][x])
		{
			if (is_walkable(og->grid[y][x]) && map_copy[y][x] != 'V')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
