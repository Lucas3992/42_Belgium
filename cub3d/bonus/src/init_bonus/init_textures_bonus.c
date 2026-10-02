/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:56 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:57 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_size(t_txt_addr *direction, int h, int w)
{
	direction->height = h;
	direction->width = w;
}

static int	load_one_texture(t_window *win, t_txt_addr *dst, char *path)
{
	int	w;
	int	h;

	dst->img = mlx_xpm_file_to_image(win->mlx, path, &w, &h);
	if (!dst->img)
		return (1);
	update_size(dst, h, w);
	return (0);
}

int	load_textures(t_window *win, t_txt_ptr *load, t_textures *path)
{
	if (load_one_texture(win, &load->north, path->north))
		return (1);
	if (load_one_texture(win, &load->south, path->south))
		return (1);
	if (load_one_texture(win, &load->west, path->west))
		return (1);
	if (load_one_texture(win, &load->east, path->east))
		return (1);
	if (path->enemy)
	{
		if (load_one_texture(win, &load->enemy, path->enemy))
			return (1);
	}
	return (0);
}

static int	get_addr_textures(t_txt_addr *dir)
{
	dir->addr = mlx_get_data_addr(dir->img, &dir->bits_pp,
			&dir->line_len, &dir->endian);
	if (!dir->addr)
		return (1);
	return (0);
}

int	text_addr(t_game *cub)
{
	if (get_addr_textures(&cub->textures.north))
		return (1);
	if (get_addr_textures(&cub->textures.south))
		return (1);
	if (get_addr_textures(&cub->textures.west))
		return (1);
	if (get_addr_textures(&cub->textures.east))
		return (1);
	if (cub->textures.enemy.img && get_addr_textures(&cub->textures.enemy))
		return (1);
	return (0);
}
