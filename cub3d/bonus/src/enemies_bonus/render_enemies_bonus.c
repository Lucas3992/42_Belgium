/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:59:09 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:59:10 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	project_enemy(t_game *cub, t_enemy *en, t_sprite *s)
{
	if (!compute_enemy_transform(cub, en, s))
		return (0);
	compute_sprite_bounds(cub, s);
	if (s->draw_start_x >= s->draw_end_x || s->draw_start_y >= s->draw_end_y)
		return (0);
	return (1);
}

static int	init_sprite_draw(t_game *cub, t_sprite *s, int x, t_sprite_draw *d)
{
	int		sprite_w;
	double	ratio_x;
	int		sprite_start_unclipped;

	if (s->transform_y >= cub->z_buf[x])
		return (0);
	sprite_w = s->sprite_w;
	if (sprite_w <= 0)
		return (0);
	d->tex = &cub->textures.enemy;
	sprite_start_unclipped = s->screen_x - s->sprite_w / 2;
	ratio_x = (double)(x - sprite_start_unclipped) / (double)sprite_w;
	d->tex_x = (int)(ratio_x * d->tex->width);
	if (d->tex_x < 0 || d->tex_x >= d->tex->width)
		return (0);
	d->bypp = d->tex->bits_pp / 8;
	d->y = s->draw_start_y;
	return (1);
}

static void	draw_enemy_stripe(t_game *cub, t_sprite *s, int x)
{
	t_sprite_draw	draw;

	if (!init_sprite_draw(cub, s, x, &draw))
		return ;
	while (draw.y <= s->draw_end_y)
	{
		draw.ratio_y = (double)(draw.y - s->draw_start_y) / (double)s->sprite_h;
		draw.tex_y = (int)(draw.ratio_y * draw.tex->height);
		if (draw.tex_y >= 0 && draw.tex_y < draw.tex->height)
		{
			draw.src = draw.tex->addr + draw.tex_y * draw.tex->line_len
				+ draw.tex_x * draw.bypp;
			draw.color = *(unsigned int *)draw.src;
			if (!is_transparent(draw.color))
				put_pixel(cub->buffer, x, draw.y, draw.color);
		}
		draw.y++;
	}
}

static void	draw_one_enemy(t_game *cub, t_enemy *en)
{
	int			x;
	t_sprite	sprite;

	if (!project_enemy(cub, en, &sprite))
		return ;
	x = sprite.draw_start_x;
	while (x <= sprite.draw_end_x)
	{
		if (x >= 0 && x < cub->buffer->width)
			draw_enemy_stripe(cub, &sprite, x);
		x++;
	}
}

void	render_enemies(t_game *cub)
{
	int		i;
	t_enemy	*en;

	if (!cub->textures.enemy.img || !cub->textures.enemy.addr)
		return ;
	if (!cub->z_buf)
		return ;
	i = 0;
	while (i < cub->nb_enemy)
	{
		en = &cub->enemies[i];
		if (en->is_dead == 0 && en->hp > 0)
			draw_one_enemy(cub, en);
		i++;
	}
}
