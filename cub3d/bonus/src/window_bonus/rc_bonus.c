/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:47 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 11:53:40 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* direction du rayon en x negative donc rayon part sur la gauche donc 
la distance avant prochaine hitbox = position joueur - position rayon 
* la distance pour traverser la case;
si droite on inverse et on +1 la case pcq on calcule de la case a droite
*/
static void	compute_step_and_side_dist(t_rc *rc, t_game *cub)
{
	t_character	*player;

	player = &cub->player;
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (player->x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - player->x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (player->y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - player->y) * rc->delta_dist_y;
	}
}

static void	dda(t_rc *rc, t_game *cub)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (get_map_cell(cub, rc->map_x, rc->map_y) == '1')
			rc->hit = 1;
	}
}

int	compute_tex_x(t_txt_addr *tex, t_rc *rc, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (rc->side == 0 && rc->ray_dir_x < 0)
		tex_x = tex->width - tex_x -1;
	if (rc->side == 1 && rc->ray_dir_y > 0)
		tex_x = tex->width - tex_x -1;
	return (tex_x);
}

static void	cast_ray(t_game *cub, int x)
{
	t_rc	rc;

	init_rc(&rc, cub, x);
	compute_step_and_side_dist(&rc, cub);
	dda(&rc, cub);
	compute_wall_height(&rc, cub);
	cub->z_buf[x] = rc.perp_wall_dist;
	draw_wall_column(cub, &rc, x);
}

void	ultimate_rc(t_game *cub)
{
	int	x;

	x = 0;
	while (x < cub->buffer->width)
	{
		cast_ray(cub, x);
		x++;
	}
}
