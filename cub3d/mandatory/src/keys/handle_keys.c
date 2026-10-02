/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:38 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:56:39 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int key, t_game *cub)
{
	if (cub->win.win)
	{
		if (key == 65307)
			cub->keys.esc = 1;
		else if (key == 119)
			cub->keys.up = 1;
		else if (key == 97)
			cub->keys.left = 1;
		else if (key == 115)
			cub->keys.down = 1;
		else if (key == 100)
			cub->keys.right = 1;
		else if (key == 65361)
			cub->keys.a_left = 1;
		else if (key == 65363)
			cub->keys.a_right = 1;
		else if (key == 65505 && cub->keys.toggle_sprint == 0)
		{
			cub->keys.sprint = !cub->keys.sprint;
			cub->keys.toggle_sprint = 1;
		}
	}
	return (0);
}

int	handle_key_release(int key, t_game *cub)
{
	if (cub->win.win)
	{
		if (key == 65307)
			cub->keys.esc = 0;
		else if (key == 119)
			cub->keys.up = 0;
		else if (key == 97)
			cub->keys.left = 0;
		else if (key == 115)
			cub->keys.down = 0;
		else if (key == 100)
			cub->keys.right = 0;
		else if (key == 65361)
			cub->keys.a_left = 0;
		else if (key == 65363)
			cub->keys.a_right = 0;
		else if (key == 65505)
			cub->keys.toggle_sprint = 0;
	}
	return (0);
}

static void	handle_sprint_and_shoot(t_game *cub, double *move_speed)
{
	if (cub->keys.sprint == 1)
		*move_speed *= 2.0;
}

void	apply_inputs(t_game *c, double delta)
{
	double	mv_spd;
	double	rot_speed;
	double	move_y;
	double	move_x;

	mv_spd = c->player.move_speed * delta * 30;
	handle_sprint_and_shoot(c, &mv_spd);
	rot_speed = c->player.rot_speed * delta * 40;
	if (c->keys.esc == 1)
		clean_explicit_exit(c, 0, NULL);
	if (c->keys.a_left == 1)
		rotate_player(c, -rot_speed);
	if (c->keys.a_right == 1)
		rotate_player(c, rot_speed);
	move_y = c->player.dir_y * mv_spd;
	move_x = c->player.dir_x * mv_spd;
	if (c->keys.up == 1)
		mov_plyr(c, move_x, move_y);
	if (c->keys.down == 1)
		mov_plyr(c, -move_x, -move_y);
	if (c->keys.left == 1)
		mov_plyr(c, -c->player.plane_x * mv_spd, -c->player.plane_y * mv_spd);
	if (c->keys.right == 1)
		mov_plyr(c, c->player.plane_x * mv_spd, c->player.plane_y * mv_spd);
}
