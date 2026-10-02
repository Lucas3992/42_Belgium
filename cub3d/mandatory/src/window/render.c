/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:55:37 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 11:50:17 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	offset = distance entre premier octet et loctet quon veut atteindre;
	/8 -> convertit le nb de bits par pixels en octets;
	donc ici on calcule quel pixel colorier*/
void	put_pixel(t_frame *buf, int x, int y, unsigned int color)
{
	int		bypp;
	int		offset;
	char	*pixel_to_fill;

	if ((x < 0 || y < 0) || x >= buf->width || y >= buf->height)
		return ;
	bypp = buf->bits_pp / 8;
	offset = (y * buf->line_len) + (x * bypp);
	pixel_to_fill = buf->address + offset;
	*(unsigned int *)pixel_to_fill = color;
}

void	render_background(t_frame *buf, unsigned int s_clr, unsigned int f_clr)
{
	int	x;
	int	y;

	y = 0;
	while (y < buf->height / 2)
	{
		x = 0;
		while (x < buf->width)
			put_pixel(buf, x++, y, s_clr);
		y++;
	}
	while (y < buf->height)
	{
		x = 0;
		while (x < buf->width)
			put_pixel(buf, x++, y, f_clr);
		y++;
	}
}

int	render_scene(t_game *cub)
{
	render_background(cub->buffer, cub->buffer->sky_argb,
		cub->buffer->floor_argb);
	ultimate_rc(cub);
	mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->buffer->img, 0, 0);
	return (0);
}

char	get_map_cell(t_game *cub, int x, int y)
{
	char	c;

	if (y < 0 || y >= cub->map.height)
		return ('1');
	if (!cub->map.grid[y])
		return ('1');
	if (x < 0 || x >= (int)ft_strlen(cub->map.grid[y]))
		return ('1');
	c = cub->map.grid[y][x];
	if (c == ' ' || c == '\t')
		return ('1');
	return (c);
}
