/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:39:15 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 12:18:54 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_and_create_mlx_window(t_game *game)
{
	int	width;
	int	height;

	game->mlx_init = mlx_init();
	if (!game->mlx_init)
		explicit_error_and_exit("Failed to initialize mlx", game);
	width = game->map.x * TILE_SIZE;
	height = game->map.y * TILE_SIZE;
	game->window = mlx_new_window(game->mlx_init, width, height, "so_long");
	if (!game->window)
		explicit_error_and_exit("Failed to create the window", game);
}

void	charging_sprites(t_game *game)
{
	int	x;
	int	y;

	game->img.player = mlx_xpm_file_to_image(game->mlx_init,
			"graphic/sprites/player.xpm", &x, &y);
	if (!game->img.player)
		explicit_error_and_exit("Could'nt load player sprite", game);
	game->img.wall = mlx_xpm_file_to_image(game->mlx_init,
			"graphic/sprites/wall.xpm", &x, &y);
	if (!game->img.wall)
		explicit_error_and_exit("Could'nt load wall sprite", game);
	game->img.floor = mlx_xpm_file_to_image(game->mlx_init,
			"graphic/sprites/floor.xpm", &x, &y);
	if (!game->img.floor)
		explicit_error_and_exit("Could'nt load floor sprite", game);
	game->img.collectible = mlx_xpm_file_to_image(game->mlx_init,
			"graphic/sprites/collectible.xpm", &x, &y);
	if (!game->img.collectible)
		explicit_error_and_exit("Could'nt load collectible sprite", game);
	game->img.exit = mlx_xpm_file_to_image(game->mlx_init,
			"graphic/sprites/exit.xpm", &x, &y);
	if (!game->img.exit)
		explicit_error_and_exit("Could'nt load exit sprite", game);
}

static void	put_right_sprite_to_tile(t_game *game, int x, int y)
{
	int	sx;
	int	sy;

	sx = x * TILE_SIZE;
	sy = y * TILE_SIZE;
	mlx_put_image_to_window(game->mlx_init,
		game->window, game->img.floor, sx, sy);
	if (game->map.grid[y][x] == '1')
		mlx_put_image_to_window(game->mlx_init,
			game->window, game->img.wall, sx, sy);
	else if (game->map.grid[y][x] == 'E')
		mlx_put_image_to_window(game->mlx_init,
			game->window, game->img.exit, sx, sy);
	else if (game->map.grid[y][x] == 'C')
		mlx_put_image_to_window(game->mlx_init,
			game->window, game->img.collectible, sx, sy);
	if (x == game->player_x && y == game->player_y)
		mlx_put_image_to_window(game->mlx_init,
			game->window, game->img.player, sx, sy);
}

void	display_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.y)
	{
		x = 0;
		while (x < game->map.x)
		{
			put_right_sprite_to_tile(game, x, y);
			x++;
		}
		y++;
	}
}
