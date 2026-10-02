/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:59:12 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:59:12 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	count_enemies(t_map *map)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'M')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	place_enemy(t_game *cub, int x, int y, int *i)
{
	t_enemy	*en;

	en = &cub->enemies[*i];
	en->x = x + 0.5;
	en->y = y + 0.5;
	en->hp = 1;
	en->is_dead = 0;
	cub->map.grid[y][x] = '0';
	*i += 1;
}

static void	fill_enemies_from_map(t_game *cub)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (cub->map.grid[y][x])
		{
			if (cub->map.grid[y][x] == 'M')
				place_enemy(cub, x, y, &i);
			x++;
		}
		y++;
	}
}

int	init_enemies(t_game *cub)
{
	int	count;

	count = count_enemies(&cub->map);
	cub->nb_enemy = count;
	if (count <= 0)
	{
		cub->enemies = NULL;
		return (0);
	}
	cub->enemies = malloc(sizeof(t_enemy) * count);
	if (!cub->enemies)
	{
		cub->nb_enemy = 0;
		return (1);
	}
	fill_enemies_from_map(cub);
	return (0);
}
