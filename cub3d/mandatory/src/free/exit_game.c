/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:53 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:56:57 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_buffer(t_game *cub)
{
	if (cub->buffer)
	{
		if (cub->buffer->img)
			mlx_destroy_image(cub->win.mlx, cub->buffer->img);
		free(cub->buffer);
		cub->buffer = NULL;
	}
}

void	free_win(t_window *win)
{
	if (!win)
		return ;
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	if (win->mlx)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
	}
	ft_bzero(win, sizeof(t_window));
}

void	free_game(t_game *cub)
{
	get_next_line(-1);
	if (!cub)
		return ;
	free_texture_images(&cub->win, &cub->textures);
	destroy_buffer(cub);
	if (cub->map.grid)
		free_array(cub->map.grid);
	free_win(&cub->win);
}

void	clean_explicit_exit(t_game *cub, int ret, char *msg)
{
	free_game(cub);
	if (msg)
		printf("%s", msg);
	exit (ret);
}

int	free_map_data_and_fail(t_game *cub, t_map_config *map_data)
{
	if (map_data)
	{
		if (map_data->map.grid)
			free_array(map_data->map.grid);
		free_textures(&map_data->textures);
		free(map_data);
	}
	free_game(cub);
	return (1);
}
