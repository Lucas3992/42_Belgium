/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:48 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:57:49 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_crosshair(t_frame *buf, unsigned int color)
{
	int	cx;
	int	cy;

	cx = buf->width / 2;
	cy = buf->height / 2;
	put_pixel(buf, cx - 1, cy - 1, color);
	put_pixel(buf, cx, cy - 1, color);
	put_pixel(buf, cx + 1, cy - 1, color);
	put_pixel(buf, cx - 1, cy, color);
	put_pixel(buf, cx, cy, color);
	put_pixel(buf, cx + 1, cy, color);
	put_pixel(buf, cx - 1, cy + 1, color);
	put_pixel(buf, cx, cy + 1, color);
	put_pixel(buf, cx + 1, cy + 1, color);
}

void	render_hud(t_game *cub)
{
	draw_crosshair(cub->buffer, 0xFFFFFFFF);
	if (cub->hitmarker_timer > 0)
		draw_hitmarker(cub->buffer, 0xFFFFFFFF);
}
