/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:58 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:58 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	setup_game(t_game *cub, t_map_config *map_data, char *map_path)
{
	if (map_init(map_path, cub, map_data))
		return (free_map_data_and_fail(cub, map_data));
	if (load_textures(&cub->win, &cub->textures, &map_data->textures))
		return (free_map_data_and_fail(cub, map_data));
	if (text_addr(cub))
		return (free_map_data_and_fail(cub, map_data));
	cub->buffer = init_buffer(cub, map_data);
	if (!cub->buffer)
		return (free_map_data_and_fail(cub, map_data));
	cub->z_buf = malloc(sizeof(double) * cub->buffer->width);
	if (!cub->z_buf)
		return (free_map_data_and_fail(cub, map_data));
	if (init_player(cub))
		return (free_map_data_and_fail(cub, map_data));
	if (init_enemies(cub))
		return (free_map_data_and_fail(cub, map_data));
	init_weapon(cub);
	cub->hitmarker_timer = 0;
	cub->sound_level = 100;
	init_minimap(cub);
	return (0);
}

int	init_game(t_game *cub, char *map_path)
{
	t_map_config	*map_data;

	if (init_window(&cub->win))
		return (1);
	map_data = malloc(sizeof(t_map_config));
	if (!map_data)
	{
		free_game(cub);
		return (1);
	}
	ft_bzero(map_data, sizeof(t_map_config));
	if (setup_game(cub, map_data, map_path))
		return (1);
	free_textures(&map_data->textures);
	free(map_data);
	return (0);
}
