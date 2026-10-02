/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:47 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 13:03:33 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate_player(t_game *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * cos(angle)
		- cub->player.dir_y * sin(angle);
	cub->player.dir_y = old_dir_x * sin(angle) + cub->player.dir_y * cos(angle);
	cub->player.plane_x = cub->player.plane_x * cos(angle)
		- cub->player.plane_y * sin(angle);
	cub->player.plane_y = old_plane_x * sin(angle)
		+ cub->player.plane_y * cos(angle);
}

void	mov_plyr(t_game *cub, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x + dx;
	new_y = cub->player.y + dy;
	if (get_map_cell(cub, (int)(cub->player.x), (int)new_y) != '1')
		cub->player.y = new_y;
	if (get_map_cell(cub, (int)new_x, (int)(cub->player.y)) != '1')
		cub->player.x = new_x;
}
