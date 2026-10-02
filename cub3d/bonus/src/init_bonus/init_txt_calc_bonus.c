/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_txt_calc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:55 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:55 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_txt_calc(t_txt_calc *tc, t_rc *rc, t_game *cub, t_txt_addr *ta)
{
	tc->step = (double)ta->height / (double)rc->line_height;
	tc->tex_pos = rc->draw_start - (cub->buffer->height / 2)
		+ (rc->line_height / 2);
	tc->tex_pos = tc->tex_pos * tc->step;
}
