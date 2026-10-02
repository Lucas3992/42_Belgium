/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:48 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:48 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_quit(t_game *cub)
{
	if (cub->win.win)
		clean_explicit_exit(cub, 0, NULL);
	return (0);
}
