/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:35 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:36 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	map_init(char *map_name, t_game *cub, t_map_config *data)
{
	data->map_path = map_name;
	if (check_cub(map_name))
		return (1);
	if (read_map(map_name, data))
		return (1);
	if (!validate_map(&data->map))
		return (1);
	cub->map = data->map;
	return (0);
}

void	fill_cardinal(char *cardinal[7])
{
	cardinal[0] = "NO";
	cardinal[1] = "SO";
	cardinal[2] = "WE";
	cardinal[3] = "EA";
	cardinal[4] = "F";
	cardinal[5] = "C";
	cardinal[6] = "M";
}
