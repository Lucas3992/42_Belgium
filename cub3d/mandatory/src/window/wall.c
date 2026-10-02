/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:55:30 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:55:32 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_wall_height(t_rc *rc, t_game *cub)
{
	if (rc->side == 0)
		rc->perp_wall_dist = rc->side_dist_x - rc->delta_dist_x;
	else
		rc->perp_wall_dist = rc->side_dist_y - rc->delta_dist_y;
	rc->line_height = (int)cub->buffer->height / rc->perp_wall_dist;
	rc->draw_start = (cub->buffer->height / 2) - (rc->line_height / 2);
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = (rc->line_height / 2) + (cub->buffer->height / 2);
	if (rc->draw_end >= cub->buffer->height)
		rc->draw_end = cub->buffer->height -1;
}

t_txt_addr	*which_wall_texture(t_game *cub, t_rc *rc)
{
	if (rc->side == 0 && rc->ray_dir_x > 0)
		return (&cub->textures.east);
	else if (rc->side == 0 && rc->ray_dir_x < 0)
		return (&cub->textures.west);
	else if (rc->side == 1 && rc->ray_dir_y > 0)
		return (&cub->textures.south);
	return (&cub->textures.north);
}

double	compute_wall_x(t_game *cub, t_rc *rc)
{
	double		wall_x;
	t_character	*player;

	player = &cub->player;
	if (rc->side == 0)
		wall_x = player->y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		wall_x = player->x + rc->perp_wall_dist * rc->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static void	draw_textured_column(t_game *cub, t_rc *rc, t_txt_addr *tex, int x)
{
	t_txt_calc		tc;
	double			wall_x;
	int				y;
	int				tex_y;
	char			*src;

	wall_x = compute_wall_x(cub, rc);
	tc.tex_x = compute_tex_x(tex, rc, wall_x);
	init_txt_calc(&tc, rc, cub, tex);
	y = rc->draw_start;
	while (y <= rc->draw_end)
	{
		tex_y = (int)tc.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height -1;
		src = tex->addr + tex_y * tex->line_len + tc.tex_x * (tex->bits_pp / 8);
		put_pixel(cub->buffer, x, y, *(unsigned int *)src);
		tc.tex_pos += tc.step;
		y++;
	}
}

void	draw_wall_column(t_game *cub, t_rc *rc, int x)
{
	t_txt_addr	*tex;

	tex = which_wall_texture(cub, rc);
	draw_textured_column(cub, rc, tex, x);
}
