/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:48 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:56:49 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_size(t_txt_addr *direction, int h, int w)
{
	direction->height = h;
	direction->width = w;
}

int	load_textures(t_window *win, t_txt_ptr *load, t_textures *path)
{
	int	w;
	int	h;

	load->north.img = mlx_xpm_file_to_image(win->mlx, path->north, &w, &h);
	if (!load->north.img)
		return (1);
	update_size(&load->north, h, w);
	load->south.img = mlx_xpm_file_to_image(win->mlx, path->south, &w, &h);
	if (!load->south.img)
		return (1);
	update_size(&load->south, h, w);
	load->west.img = mlx_xpm_file_to_image(win->mlx, path->west, &w, &h);
	if (!load->west.img)
		return (1);
	update_size(&load->west, h, w);
	load->east.img = mlx_xpm_file_to_image(win->mlx, path->east, &w, &h);
	if (!load->east.img)
		return (1);
	update_size(&load->east, h, w);
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
	return (0);
}
