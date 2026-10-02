/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:44:04 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 09:58:23 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_destination(t_game *game, int dest_x, int dest_y)
{
	int	dest_tile;

	dest_tile = game->map.grid[dest_y][dest_x];
	if (dest_tile == '1')
		return (0);
	else if (dest_tile == '0')
		return (1);
	else if (dest_tile == 'C')
		return (2);
	else if (dest_tile == 'E')
		return (3);
	return (-1);
}

void	move_up(t_game *game)
{
	int		dest;
	t_move	m;
	char	old_tile;

	m.old_x = game->player_x;
	m.old_y = game->player_y;
	m.new_x = game->player_x;
	m.new_y = game->player_y -1;
	old_tile = game->map.grid[game->player_y][game->player_x];
	dest = handle_destination(game, m.new_x, m.new_y);
	if (dest == 0)
		return ;
	if (dest == 2)
		game->remaining_collectibles--;
	else if (dest == 3)
		is_game_successfully_over(game, m.new_x, m.new_y);
	swap_tiles(game, m, old_tile);
	game->player_x = m.new_x;
	game->player_y = m.new_y;
	game->move_count++;
	ft_printf("Move count : %d\n", game->move_count);
	display_map(game);
}

void	move_down(t_game *game)
{
	int		dest;
	t_move	m;
	char	old_tile;

	m.old_x = game->player_x;
	m.old_y = game->player_y;
	m.new_x = game->player_x;
	m.new_y = game->player_y +1;
	old_tile = game->map.grid[game->player_y][game->player_x];
	dest = handle_destination(game, m.new_x, m.new_y);
	if (dest == 0)
		return ;
	if (dest == 2)
		game->remaining_collectibles--;
	else if (dest == 3)
		is_game_successfully_over(game, m.new_x, m.new_y);
	swap_tiles(game, m, old_tile);
	game->player_x = m.new_x;
	game->player_y = m.new_y;
	game->move_count++;
	ft_printf("Move count : %d\n", game->move_count);
	display_map(game);
}

void	move_left(t_game *game)
{
	int		dest;
	t_move	m;
	char	old_tile;

	m.old_x = game->player_x;
	m.old_y = game->player_y;
	m.new_x = game->player_x -1;
	m.new_y = game->player_y;
	old_tile = game->map.grid[game->player_y][game->player_x];
	dest = handle_destination(game, m.new_x, m.new_y);
	if (dest == 0)
		return ;
	if (dest == 2)
		game->remaining_collectibles--;
	else if (dest == 3)
		is_game_successfully_over(game, m.new_x, m.new_y);
	swap_tiles(game, m, old_tile);
	game->player_x = m.new_x;
	game->player_y = m.new_y;
	game->move_count++;
	ft_printf("Move count : %d\n", game->move_count);
	display_map(game);
}

void	move_right(t_game *game)
{
	int		dest;
	t_move	m;
	char	old_tile;

	m.old_x = game->player_x;
	m.old_y = game->player_y;
	m.new_x = game->player_x +1;
	m.new_y = game->player_y;
	old_tile = game->map.grid[game->player_y][game->player_x];
	dest = handle_destination(game, m.new_x, m.new_y);
	if (dest == 0)
		return ;
	if (dest == 2)
		game->remaining_collectibles--;
	else if (dest == 3)
		is_game_successfully_over(game, m.new_x, m.new_y);
	swap_tiles(game, m, old_tile);
	game->player_x = m.new_x;
	game->player_y = m.new_y;
	game->move_count++;
	ft_printf("Move count : %d\n", game->move_count);
	display_map(game);
}
