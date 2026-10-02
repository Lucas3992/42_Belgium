/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:20 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 13:54:38 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap_tile(t_game *cub, int map_x, int map_y)
{
	int		screen_x;
	int		screen_y;
	int		color;
	char	cell;

	screen_x = cub->minimap.x_map + map_x * cub->minimap.tile_size;
	screen_y = cub->minimap.y_map + map_y * cub->minimap.tile_size;
	cell = get_map_cell(cub, map_x, map_y);
	if (cell == '1')
		color = cub->minimap.wall_color;
	else if (cell == '0')
		color = cub->minimap.floor_color;
	else
		return ;
	draw_square(cub, screen_x, screen_y, color);
}

void	draw_square(t_game *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->minimap.tile_size)
	{
		j = 0;
		while (j < cub->minimap.tile_size)
		{
			if (x + j >= 0 && x + j < cub->win.width
				&& y + i >= 0 && y + i < cub->win.height)
				my_mlx_pixel_put(cub->buffer, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_dot(t_game *cub, int center_x, int center_y)
{
	int	x;
	int	y;
	int	radius;

	radius = 3;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel_safe(cub, center_x + x,
					center_y + y, cub->minimap.player_color);
			x++;
		}
		y++;
	}
}

void	put_pixel_safe(t_game *cub, int x, int y, int color)
{
	if (x >= 0 && x < cub->win.width && y >= 0 && y < cub->win.height)
		my_mlx_pixel_put(cub->buffer, x, y, color);
}

void	my_mlx_pixel_put(t_frame *buffer, int x, int y, int color)
{
	char	*dst;

	dst = buffer->address + (y * buffer->line_len + x * (buffer->bits_pp / 8));
	*(unsigned int *)dst = color;
}
