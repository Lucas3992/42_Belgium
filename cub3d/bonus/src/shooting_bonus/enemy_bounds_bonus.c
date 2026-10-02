/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bounds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:11 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:12 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	enemy_transform(t_game *cub, t_enemy *en, t_enemy_proj *p)
{
	t_character	*pl;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;

	pl = &cub->player;
	sprite_x = en->x - pl->x;
	sprite_y = en->y - pl->y;
	inv_det = pl->plane_x * pl->dir_y - pl->dir_x * pl->plane_y;
	if (inv_det == 0.0)
		return (0);
	inv_det = 1.0 / inv_det;
	p->transform_x = inv_det * (pl->dir_y * sprite_x - pl->dir_x * sprite_y);
	p->transform_y = inv_det * (-pl->plane_y * sprite_x + pl->plane_x
			* sprite_y);
	if (p->transform_y <= 0.0)
		return (0);
	return (1);
}

static void	enemy_vertical_bounds(t_game *cub, t_enemy_proj *p)
{
	t_frame	*f;
	int		h;

	f = cub->buffer;
	h = (int)(f->height / p->transform_y);
	p->h = h;
	p->start_y = -h / 2 + f->height / 2;
	if (p->start_y < 0)
		p->start_y = 0;
	p->end_y = h / 2 + f->height / 2;
	if (p->end_y >= f->height)
		p->end_y = f->height - 1;
}

static void	enemy_horizontal_bounds(t_game *cub, t_enemy_proj *p)
{
	t_frame	*f;
	int		w;

	f = cub->buffer;
	p->screen_x = (int)((f->width / 2.0)
			* (1.0 + p->transform_x / p->transform_y));
	w = p->h;
	p->w = w;
	p->start_x = -w / 2 + p->screen_x;
	if (p->start_x < 0)
		p->start_x = 0;
	p->end_x = w / 2 + p->screen_x;
	if (p->end_x >= f->width)
		p->end_x = f->width - 1;
}

int	build_enemy_proj(t_game *cub, t_enemy *en, t_enemy_proj *p)
{
	if (!enemy_transform(cub, en, p))
		return (0);
	enemy_vertical_bounds(cub, p);
	enemy_horizontal_bounds(cub, p);
	if (p->start_x >= p->end_x || p->start_y >= p->end_y)
		return (0);
	p->tex = &cub->textures.enemy;
	return (1);
}
