/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fps_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:50 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:57:51 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	display_fps(t_game *cub, double delta)
{
	static double	accum_time = 0.0;
	static int		fps = 0;
	static int		frame_count = 0;
	char			text[32];

	accum_time = accum_time + delta;
	frame_count++;
	if (accum_time >= 1.0)
	{
		fps = (int)(frame_count / accum_time);
		accum_time = 0.0;
		frame_count = 0;
	}
	snprintf(text, sizeof(text), "FPS: %d", fps);
	mlx_string_put(cub->win.mlx, cub->win.win, 20, 20, 0xFFFFFF, text);
}
