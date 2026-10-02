/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:45 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/01 12:37:28 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_player(t_game *cub)
{
	int			x;
	int			y;
	t_character	tmp;

	x = (int)cub->map.data->player.x;
	y = (int)cub->map.data->player.y;
	tmp.x = cub->map.data->player.x + 0.5;
	tmp.y = cub->map.data->player.y + 0.5;
	assign_directions(cub->map.data->player.pov, &tmp);
	tmp.plane_x = -(tmp.dir_y) * 0.66;
	tmp.plane_y = tmp.dir_x * 0.66;
	tmp.move_speed = 0.07;
	tmp.rot_speed = 0.05;
	tmp.hp = 3;
	tmp.money = 0;
	cub->player = tmp;
	cub->map.grid[y][x] = '0';
	return (0);
}

int	init_window(t_window *win)
{
	win->width = 1280;
	win->height = 720;
	win->mlx = mlx_init();
	if (!win->mlx)
		return (1);
	win->win = mlx_new_window(win->mlx, win->width, win->height, "cub3d");
	if (!win->win)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		win->mlx = NULL;
		return (1);
	}
	return (0);
}

t_frame	*init_buffer(t_game *game, t_map_config *data)
{
	t_frame	*buf;

	buf = malloc(sizeof(t_frame));
	if (!buf)
		return (NULL);
	buf->height = game->win.height;
	buf->width = game->win.width;
	buf->sky_argb = rgb_to_argb(data->textures.ceiling);
	buf->floor_argb = rgb_to_argb(data->textures.floor);
	buf->img = mlx_new_image(game->win.mlx, buf->width, buf->height);
	if (!buf->img)
		return (free(buf), NULL);
	buf->address = mlx_get_data_addr(buf->img,
			&buf->bits_pp, &buf->line_len, &buf->endian);
	if (!buf->address || buf->bits_pp != 32)
	{
		mlx_destroy_image(game->win.mlx, buf->img);
		free(buf);
		return (NULL);
	}
	return (buf);
}

void	init_rc(t_rc *rc, t_game *cub, int x)
{
	double		cam_x;
	t_character	*player;

	player = &cub->player;
	cam_x = 2.0 * x / (double)cub->buffer->width - 1.0;
	rc->camera_x = cam_x;
	rc->ray_dir_x = player->dir_x + player->plane_x * cam_x;
	rc->ray_dir_y = player->dir_y + player->plane_y * cam_x;
	rc->map_x = (int)player->x;
	rc->map_y = (int)player->y;
	if (rc->ray_dir_x == 0)
		rc->delta_dist_x = 1e30;
	else
		rc->delta_dist_x = fabs(1.0 / rc->ray_dir_x);
	if (rc->ray_dir_y == 0)
		rc->delta_dist_y = 1e30;
	else
		rc->delta_dist_y = fabs(1.0 / rc->ray_dir_y);
	rc->hit = 0;
}

int	init_game(t_game *cub, char *map_path)
{
	t_map_config	*map_data;

	if (init_window(&cub->win))
		return (1);
	map_data = malloc(sizeof(t_map_config));
	if (!map_data)
		return (free_game(cub), 1);
	ft_bzero(map_data, sizeof(t_map_config));
	map_data->game = cub;
	if (map_init(map_path, cub, map_data))
		return (free_map_data_and_fail(cub, map_data));
	if (load_textures(&cub->win, &cub->textures, &map_data->textures))
		return (free_map_data_and_fail(cub, map_data));
	if (text_addr(cub))
		return (free_map_data_and_fail(cub, map_data));
	cub->buffer = init_buffer(cub, map_data);
	if (!cub->buffer)
		return (free_map_data_and_fail(cub, map_data));
	if (init_player(cub))
		return (free_map_data_and_fail(cub, map_data));
	free_textures(&map_data->textures);
	free(map_data);
	return (0);
}
