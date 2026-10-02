/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:44 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:45 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_game	cub;

	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3D map.cub\n");
		return (1);
	}
	ft_bzero(&cub, sizeof(t_game));
	cub.music_id = 0;
	if (init_game(&cub, av[1]))
		clean_explicit_exit(&cub, 1, "Failed to initialize game\n");
	start_music(&cub);
	mlx_hook(cub.win.win, 17, 0, mouse_quit, &cub);
	mlx_hook(cub.win.win, 2, 1L << 0, handle_key_press, &cub);
	mlx_hook(cub.win.win, 3, 1L << 1, handle_key_release, &cub);
	mlx_loop_hook(cub.win.mlx, game_loop, &cub);
	mlx_loop(cub.win.mlx);
	stop_music(&cub);
	clean_explicit_exit(&cub, 0, NULL);
	return (0);
}

int	game_loop(t_game *cub)
{
	double			delta;
	double			now;
	static double	last = 0.0;

	now = now_in_seconds();
	if (last == 0.0)
		last = now;
	delta = now - last;
	if (delta > 0.1)
		delta = 0.1;
	last = now;
	apply_inputs(cub, delta);
	render_scene(cub);
	update_hitmarker(cub);
	draw_weapon(cub);
	display_fps(cub, delta);
	display_score(cub);
	return (0);
}
