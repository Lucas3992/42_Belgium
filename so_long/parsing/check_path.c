/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:19:46 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/22 09:35:58 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	dup_map(t_map map, t_game *game)
{
	int		y;
	t_map	copy;

	copy.grid = malloc((map.y +1) * sizeof(char *));
	if (!copy.grid)
		explicit_error_and_exit("Malloc failed", game);
	y = 0;
	while (map.grid[y])
	{
		copy.grid[y] = ft_strdup(map.grid[y]);
		y++;
	}
	copy.grid[y] = NULL;
	copy.x = map.x;
	copy.y = map.y;
	return (copy);
}

static t_game	find_player_position(t_map map, t_game game)
{
	int	x;
	int	y;
	int	found_p;

	y = 0;
	found_p = 0;
	while (map.grid[y])
	{
		x = 0;
		while (map.grid[y][x])
		{
			if (map.grid[y][x] == 'P')
			{
				found_p++;
				game.player_x = x;
				game.player_y = y;
				return (game);
			}
			x++;
		}
		y++;
	}
	explicit_error_and_exit("The game needs exactly one player", &game);
	return (game);
}

static int	c_or_e_left(t_map copy)
{
	int	x;
	int	y;

	y = 0;
	while (copy.grid[y])
	{
		x = 0;
		while (copy.grid[y][x])
		{
			if (copy.grid[y][x] == 'C')
				return (1);
			else if (copy.grid[y][x] == 'E')
				return (2);
			x++;
		}
		y++;
	}
	return (0);
}

//marque la tile avec V si visitee
static void	visit_all_tile(char **map, int x, int y)
{
	char	t;

	t = map[y][x];
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return ;
	if (t != '0' && t != 'C' && t != 'E' && t != 'P')
		return ;
	map[y][x] = 'V';
	visit_all_tile(map, x -1, y);
	visit_all_tile(map, x +1, y);
	visit_all_tile(map, x, y -1);
	visit_all_tile(map, x, y +1);
}

void	game_is_playable(t_map map, t_game *game)
{
	t_map	copy;
	t_game	tmp;

	copy = dup_map(map, game);
	tmp = find_player_position(map, *game);
	game->player_x = tmp.player_x;
	game->player_y = tmp.player_y;
	visit_all_tile(copy.grid, tmp.player_x, tmp.player_y);
	if (c_or_e_left(copy) == 1)
	{
		free_grid(copy.grid);
		explicit_error_and_exit("Player can't reach all collectibles", game);
	}
	else if (c_or_e_left(copy) == 2)
	{
		free_grid(copy.grid);
		explicit_error_and_exit("Player can't reach the exit", game);
	}
	free_grid(copy.grid);
}
