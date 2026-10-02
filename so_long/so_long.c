/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:12:16 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 15:32:48 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/* 
void	print_map(t_map map)
{
    int	i = 0;
    while (map.grid[i])
    {
        printf("%s\n", map.grid[i]);
        i++;
    }
} */

static int	key_handler(int key, t_game *game)
{
	if (game->window)
	{
		if (key == 65307)
		{
			free_game(game);
			exit (0);
		}
		else if (key == 119 || key == 65362)
			move_up(game);
		else if (key == 97 || key == 65361)
			move_left(game);
		else if (key == 115 || key == 65364)
			move_down(game);
		else if (key == 100 || key == 65363)
			move_right(game);
		game->current_key = key;
	}
	return (0);
}

static int	mouse_quit(t_game *game)
{
	if (game->window)
		free_game(game);
	exit (0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (arguments_are_valid(ac, av[1], &game))
	{
		game.move_count = 0;
		parse_map(av[1], &game);
		init_and_create_mlx_window(&game);
		charging_sprites(&game);
		display_map(&game);
		mlx_hook(game.window, 17, 0, mouse_quit, &game);
		mlx_key_hook(game.window, key_handler, &game);
		mlx_loop(game.mlx_init);
	}
	return (0);
}
