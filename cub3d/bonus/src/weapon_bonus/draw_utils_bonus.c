/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:57 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:57:58 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*get_weapon_addr(t_weapon *weapon)
{
	if (weapon->is_firing)
		return (weapon->addr_fire);
	return (weapon->addr_idle);
}

void	update_weapon_fire(t_weapon *weapon)
{
	weapon->fire_frame++;
	if (weapon->fire_frame > 10)
	{
		weapon->is_firing = 0;
		weapon->fire_frame = 0;
	}
}

void	process_weapon_row(t_game *game, t_weapon_draw *wd, int y)
{
	int		dst_y;
	char	*row_addr;
	t_point	dst;

	dst_y = wd->start_y + y;
	if (dst_y >= 0 && dst_y < game->buffer->height)
	{
		row_addr = wd->addr + y * wd->wp->line_len;
		dst.x = wd->start_x;
		dst.y = dst_y;
		draw_weapon_row(game, wd->wp, row_addr, dst);
	}
}
