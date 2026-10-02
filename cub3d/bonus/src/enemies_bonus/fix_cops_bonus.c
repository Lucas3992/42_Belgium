/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_cops_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:59:11 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:59:11 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_transparent(unsigned int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (r == 255 && g == 0 && b == 255)
		return (1);
	return (0);
}

void	update_enemy_distances(t_game *cub)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < cub->nb_enemy)
	{
		dx = cub->player.x - cub->enemies[i].x;
		dy = cub->player.y - cub->enemies[i].y;
		cub->enemies[i].dist = dx * dx + dy * dy;
		i++;
	}
}

static void	swap_enemies(t_enemy *a, t_enemy *b)
{
	t_enemy	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_enemies_by_distance(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->nb_enemy - 1)
	{
		j = i + 1;
		while (j < cub->nb_enemy)
		{
			if (cub->enemies[i].dist < cub->enemies[j].dist)
				swap_enemies(&cub->enemies[i], &cub->enemies[j]);
			j++;
		}
		i++;
	}
}
