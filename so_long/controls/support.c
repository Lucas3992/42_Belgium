/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:35:45 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 14:39:21 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	swap_tiles(t_game *game, t_move m, char old_tile)
{
	char	dest_tile;

	dest_tile = game->map.grid[m.new_y][m.new_x];
	if (game->map.grid[m.old_y][m.old_x] == 'P')
	{
		if (old_tile == 'E')
			game->map.grid[m.old_y][m.old_x] = 'E';
		else
			game->map.grid[m.old_y][m.old_x] = '0';
	}
	if (!(dest_tile == 'E' && game->remaining_collectibles > 0))
		game->map.grid[m.new_y][m.new_x] = 'P';
}

void	is_game_successfully_over(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == 'E' && game->remaining_collectibles == 0)
	{
		write(1, "GG BG\n", 7);
		free_game(game);
		exit(0);
	}
}
