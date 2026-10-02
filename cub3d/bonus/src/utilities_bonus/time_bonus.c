/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:00 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:01 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	now_in_seconds(void)
{
	double			now;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec + (tv.tv_usec / 1000000.0);
	return (now);
}
