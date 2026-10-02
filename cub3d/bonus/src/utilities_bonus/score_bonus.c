/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:02 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:02 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_math_random(int min, int max)
{
	return ((rand() % (max - min +1)) + min);
}

void	update_score(t_game *cub)
{
	cub->player.money += ft_math_random(0, 5);
}

void	display_score(t_game *cub)
{
	char	text[32];

	snprintf(text, sizeof(text), "%d$", cub->player.money);
	mlx_string_put(cub->win.mlx, cub->win.win, 20,
		cub->win.height -20, 0xFFFFFF, text);
}
