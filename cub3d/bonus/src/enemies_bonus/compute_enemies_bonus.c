/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_enemies_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:06:55 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 12:07:00 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	compute_enemy_transform(t_game *cub, t_enemy *en, t_sprite *sp)
{
	t_character	*p;
	double		det;

	p = &cub->player;
	sp->sprite_x = en->x - p->x;
	sp->sprite_y = en->y - p->y;
	det = p->plane_x * p->dir_y - p->dir_x * p->plane_y;
	if (det == 0.0)
		return (0);
	sp->transform_x = (p->dir_y * sp->sprite_x - p->dir_x * sp->sprite_y)
		/ det;
	sp->transform_y = (-p->plane_y * sp->sprite_x + p->plane_x
			* sp->sprite_y) / det;
	if (sp->transform_y <= 0.0001)
		return (0);
	return (1);
}

void	compute_sprite_bounds(t_game *cub, t_sprite *sp)
{
	int	h;
	int	w;
	int	center_y;

	h = cub->buffer->height;
	w = cub->buffer->width;
	sp->sprite_h = (int)(h / sp->transform_y);
	if (sp->sprite_h <= 0)
		sp->sprite_h = 1;
	sp->sprite_w = sp->sprite_h;
	sp->screen_x = (int)((w / 2.0) * (1.0 + sp->transform_x
				/ sp->transform_y));
	center_y = h / 2;
	sp->draw_start_y = center_y - sp->sprite_h / 2;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = center_y + sp->sprite_h / 2;
	if (sp->draw_end_y >= h)
		sp->draw_end_y = h - 1;
	sp->draw_start_x = sp->screen_x - sp->sprite_w / 2;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->screen_x + sp->sprite_w / 2;
	if (sp->draw_end_x >= w)
		sp->draw_end_x = w - 1;
}
