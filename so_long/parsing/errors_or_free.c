/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:13:44 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 12:05:21 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	explicit_error_and_exit(const char *msg, t_game *game)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	free_game(game);
	exit(1);
}

void	free_grid(char **map)
{
	int	i;

	if (map)
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_grid_and_exit(t_game *game, const char *msg)
{
	free_grid(game->map.grid);
	explicit_error_and_exit(msg, game);
}

static void	free_sprites(t_game *game)
{
	if (game->img.player)
		mlx_destroy_image(game->mlx_init, game->img.player);
	if (game->img.wall)
		mlx_destroy_image(game->mlx_init, game->img.wall);
	if (game->img.floor)
		mlx_destroy_image(game->mlx_init, game->img.floor);
	if (game->img.collectible)
		mlx_destroy_image(game->mlx_init, game->img.collectible);
	if (game->img.exit)
		mlx_destroy_image(game->mlx_init, game->img.exit);
}

void	free_game(t_game *game)
{
	if (game->map.grid)
		free_grid(game->map.grid);
	free_sprites(game);
	if (game->window)
		mlx_destroy_window(game->mlx_init, game->window);
	if (game->mlx_init)
	{
		mlx_destroy_display(game->mlx_init);
		free(game->mlx_init);
	}
}
