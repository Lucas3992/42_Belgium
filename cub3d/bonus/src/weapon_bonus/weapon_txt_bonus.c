/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_txt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:53 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:57:54 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_weapon_row(t_game *game, t_weapon *wp,
	char *row_addr, t_point dst)
{
	int				x;
	int				dst_x;
	int				bypp;
	char			*src;
	unsigned int	color;

	bypp = wp->bpp / 8;
	x = 0;
	while (x < wp->width)
	{
		dst_x = dst.x + x;
		if (dst_x >= 0 && dst_x < game->buffer->width)
		{
			src = row_addr + x * bypp;
			color = *(unsigned int *)src;
			if (!is_transparent(color))
				put_pixel(game->buffer, dst_x, dst.y, color);
		}
		x++;
	}
}

void	draw_weapon_image(t_game *game, t_weapon_draw *wd)
{
	int	y;

	if (!wd || !wd->wp || !wd->addr)
		return ;
	y = 0;
	while (y < wd->wp->height)
	{
		process_weapon_row(game, wd, y);
		y++;
	}
}

void	load_weapon(t_game *game, t_weapon *weapon,
	char *idle_path, char *fire_path)
{
	weapon->img_idle = mlx_xpm_file_to_image(game->win.mlx,
			idle_path, &weapon->width, &weapon->height);
	if (!weapon->img_idle)
	{
		printf("Error: Cannot load idle weapon texture: %s\n", idle_path);
		exit(1);
	}
	weapon->img_fire = mlx_xpm_file_to_image(game->win.mlx,
			fire_path, &weapon->width, &weapon->height);
	if (!weapon->img_fire)
	{
		printf("Error: Cannot load fire weapon texture: %s\n", fire_path);
		exit(1);
	}
	weapon->addr_idle = mlx_get_data_addr(weapon->img_idle,
			&weapon->bpp, &weapon->line_len, &weapon->endian);
	weapon->addr_fire = mlx_get_data_addr(weapon->img_fire,
			&weapon->bpp, &weapon->line_len, &weapon->endian);
	weapon->is_firing = 0;
	weapon->fire_frame = 0;
	weapon->damage = 25;
}
