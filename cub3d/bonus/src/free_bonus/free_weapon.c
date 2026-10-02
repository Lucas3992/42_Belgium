/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:59:02 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:59:02 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_weapon(t_game *game)
{
	if (game->player.weapon_left)
	{
		if (game->player.weapon_left->img_idle)
			mlx_destroy_image(game->win.mlx,
				game->player.weapon_left->img_idle);
		if (game->player.weapon_left->img_fire)
			mlx_destroy_image(game->win.mlx,
				game->player.weapon_left->img_fire);
		free(game->player.weapon_left);
		game->player.weapon_left = NULL;
	}
	if (game->player.weapon_right)
	{
		if (game->player.weapon_right->img_idle)
			mlx_destroy_image(game->win.mlx,
				game->player.weapon_right->img_idle);
		if (game->player.weapon_right->img_fire)
			mlx_destroy_image(game->win.mlx,
				game->player.weapon_right->img_fire);
		free(game->player.weapon_right);
		game->player.weapon_right = NULL;
	}
}
