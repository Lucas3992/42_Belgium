/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapons_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:56 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:57:56 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_weapon_positions(t_game *game, t_weapon_pos *pos)
{
	pos->x_right = game->win.width - game->player.weapon_right->width;
	pos->x_left = 0;
	pos->y = game->win.height - game->player.weapon_right->height + 120;
}

static void	render_weapons(t_game *game, t_weapon_pos *pos)
{
	t_weapon_draw	wd;

	wd.wp = game->player.weapon_left;
	wd.addr = get_weapon_addr(game->player.weapon_left);
	wd.start_x = pos->x_left;
	wd.start_y = pos->y;
	draw_weapon_image(game, &wd);
	wd.wp = game->player.weapon_right;
	wd.addr = get_weapon_addr(game->player.weapon_right);
	wd.start_x = pos->x_right;
	wd.start_y = pos->y;
	draw_weapon_image(game, &wd);
}

static void	handle_weapon_firing(t_game *game)
{
	if (game->player.weapon_right->is_firing)
		update_weapon_fire(game->player.weapon_right);
	if (game->player.weapon_left->is_firing)
		update_weapon_fire(game->player.weapon_left);
}

void	draw_weapon(t_game *game)
{
	t_weapon_pos	pos;

	if (!game->player.weapon_right || !game->player.weapon_left)
		return ;
	init_weapon_positions(game, &pos);
	render_weapons(game, &pos);
	handle_weapon_firing(game);
	mlx_put_image_to_window(game->win.mlx, game->win.win,
		game->buffer->img, 0, 0);
}
