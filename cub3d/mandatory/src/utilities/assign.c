/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:01 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:56:06 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_directions(char pov, t_character *player)
{
	if (pov == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
	else if (pov == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	else if (pov == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	else if (pov == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
}
