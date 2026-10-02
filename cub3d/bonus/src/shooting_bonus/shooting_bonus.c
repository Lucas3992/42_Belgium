/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:09 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:09 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	enemy_pixel_hit(t_game *cub, t_enemy_proj *p, int cx, int cy)
{
	t_hit_pixel	h;
	t_txt_addr	*tex;

	if (p->transform_y >= cub->z_buf[cx])
		return (0);
	h.sprite_w = p->end_x - p->start_x + 1;
	h.sprite_h = p->end_y - p->start_y + 1;
	if (h.sprite_w <= 0 || h.sprite_h <= 0)
		return (0);
	h.ratio_x = (double)(cx - p->start_x) / (double)h.sprite_w;
	h.ratio_y = (double)(cy - p->start_y) / (double)h.sprite_h;
	tex = p->tex;
	h.tex_x = (int)(h.ratio_x * (double)tex->width);
	h.tex_y = (int)(h.ratio_y * (double)tex->height);
	if (h.tex_x < 0 || h.tex_x >= tex->width
		|| h.tex_y < 0 || h.tex_y >= tex->height)
		return (0);
	h.src = tex->addr + h.tex_y * tex->line_len
		+ h.tex_x * (tex->bits_pp / 8);
	h.color = *(unsigned int *)h.src;
	if (is_transparent(h.color))
		return (0);
	return (1);
}

void	enemy_take_damage(t_enemy *en, int damage)
{
	if (damage <= 0)
		return ;
	if (en->is_dead)
		return ;
	en->hp -= damage;
	if (en->hp <= 0)
	{
		en->hp = 0;
		en->is_dead = 1;
	}
}

static int	check_enemy_hit(t_game *cub, t_hit_check *c)
{
	if (!c->en->is_dead && build_enemy_proj(cub, c->en, c->p))
	{
		if (c->h->cx >= c->p->start_x && c->h->cx <= c->p->end_x
			&& c->h->cy >= c->p->start_y && c->h->cy <= c->p->end_y)
		{
			if (enemy_pixel_hit(cub, c->p, c->h->cx, c->h->cy)
				&& (c->h->best_index == -1
					|| c->p->transform_y < c->h->best_dist))
			{
				c->h->best_dist = c->p->transform_y;
				c->h->best_index = c->index;
				return (1);
			}
		}
	}
	return (0);
}

void	shoot(t_game *cub)
{
	t_hit_ctx		h;
	t_enemy_proj	p;
	t_hit_check		c;
	int				i;

	h.cx = cub->buffer->width / 2;
	h.cy = cub->buffer->height / 2;
	h.best_dist = 0.0;
	h.best_index = -1;
	i = 0;
	while (i < cub->nb_enemy)
	{
		c.h = &h;
		c.en = &cub->enemies[i];
		c.p = &p;
		c.index = i;
		check_enemy_hit(cub, &c);
		i++;
	}
	if (h.best_index != -1)
	{
		enemy_take_damage(&cub->enemies[h.best_index], 1);
		cub->hitmarker_timer = 8;
		update_score(cub);
	}
}
