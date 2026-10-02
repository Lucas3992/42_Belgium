/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:59:28 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 13:59:29 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap(t_game *cub)
{
	draw_minimap_grid(cub);
	draw_minimap_enemies(cub);
	draw_minimap_player(cub);
}

void	init_minimap(t_game *cub)
{
	int	max_size;

	max_size = cub->map.width;
	if (cub->map.height > max_size)
		max_size = cub->map.height;
	cub->minimap.tile_size = 200 / max_size;
	if (cub->minimap.tile_size < 3)
		cub->minimap.tile_size = 3;
	cub->minimap.size = max_size * cub->minimap.tile_size;
	cub->minimap.x_map = cub->win.width -210;
	cub->minimap.y_map = 20;
	cub->minimap.wall_color = 0x000000;
	cub->minimap.floor_color = 0xFFFFFF;
	cub->minimap.player_color = 0x00FF00;
	cub->minimap.enemy_color = 0xFF0000;
}

void	draw_minimap_player(t_game *cub)
{
	int	player_x;
	int	player_y;

	player_x = cub->minimap.x_map
		+ (int)(cub->player.x * cub->minimap.tile_size);
	player_y = cub->minimap.y_map
		+ (int)(cub->player.y * cub->minimap.tile_size);
	if (player_x >= cub->minimap.x_map
		&& player_x < cub->minimap.x_map + cub->minimap.size
		&& player_y >= cub->minimap.y_map
		&& player_y < cub->minimap.y_map + cub->minimap.size)
		draw_player_dot(cub, player_x, player_y);
}

void	draw_minimap_grid(t_game *cub)
{
	int		map_x;
	int		map_y;

	map_y = 0;
	while (map_y < cub->map.height)
	{
		map_x = 0;
		while (map_x < cub->map.width)
		{
			draw_minimap_tile(cub, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}
