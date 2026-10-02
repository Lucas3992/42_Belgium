/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:23 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:24 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_enemy_dot(t_game *cub, int center_x, int center_y)
{
	int	x;
	int	y;
	int	radius;

	radius = 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel_safe(cub, center_x + x,
					center_y + y, cub->minimap.enemy_color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_enemies(t_game *cub)
{
	int		i;
	int		screen_x;
	int		screen_y;
	t_enemy	*en;

	i = 0;
	while (i < cub->nb_enemy)
	{
		en = &cub->enemies[i];
		if (!en->is_dead)
		{
			screen_x = cub->minimap.x_map
				+ (int)(en->x * cub->minimap.tile_size);
			screen_y = cub->minimap.y_map
				+ (int)(en->y * cub->minimap.tile_size);
			if (screen_x >= cub->minimap.x_map && screen_x < cub->minimap.x_map
				+ cub->minimap.size && screen_y >= cub->minimap.y_map
				&& screen_y < cub->minimap.y_map + cub->minimap.size)
				draw_enemy_dot(cub, screen_x, screen_y);
		}
		i++;
	}
}
