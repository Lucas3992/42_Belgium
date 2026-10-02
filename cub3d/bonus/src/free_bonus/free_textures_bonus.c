/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:59:03 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:59:03 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_textures(t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->enemy)
		free(textures->enemy);
}

void	free_texture_images(t_window *win, t_txt_ptr *textures)
{
	if (textures->north.img)
		mlx_destroy_image(win->mlx, textures->north.img);
	if (textures->south.img)
		mlx_destroy_image(win->mlx, textures->south.img);
	if (textures->west.img)
		mlx_destroy_image(win->mlx, textures->west.img);
	if (textures->east.img)
		mlx_destroy_image(win->mlx, textures->east.img);
	if (textures->enemy.img)
		mlx_destroy_image(win->mlx, textures->enemy.img);
}

void	free_map_data(t_map_config *data)
{
	if (!data)
		return ;
	if (data->map.grid)
		free_array(data->map.grid);
	free_textures(&data->textures);
	free(data);
}
