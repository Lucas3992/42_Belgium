/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_or_space_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:17:30 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/12/18 11:25:16 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_null_or_space(char **map, t_map *og, int y, int x)
{
	if (y < 0 || y >= og->height || x < 0)
		return (1);
	if (!map[y])
		return (1);
	if (!og->grid[y])
		return (1);
	if (x >= (int)ft_strlen(map[y]))
		return (1);
	if (x >= (int)ft_strlen(og->grid[y]))
		return (1);
	if (map[y][x] == '\0')
		return (1);
	if (map[y][x] == ' ')
		return (1);
	return (0);
}
