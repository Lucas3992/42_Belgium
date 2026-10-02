/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitmarker_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:10 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:10 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_hitmarker(t_game *cub)
{
	if (cub->hitmarker_timer > 0)
		cub->hitmarker_timer--;
}

void	draw_hitmarker(t_frame *buf, unsigned int color)
{
	int	cx;
	int	cy;
	int	i;
	int	len;

	cx = buf->width / 2;
	cy = buf->height / 2;
	len = 8;
	i = -len;
	while (i <= len)
	{
		if (i <= -5 || i >= 5)
		{
			put_pixel(buf, cx + i, cy + i, color);
			put_pixel(buf, cx + i, cy + i + 1, color);
			put_pixel(buf, cx + i, cy + i - 1, color);
			put_pixel(buf, cx + i, cy - i, color);
			put_pixel(buf, cx + i, cy - i + 1, color);
			put_pixel(buf, cx + i, cy - i - 1, color);
		}
		i++;
	}
}
