/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:16 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:17 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_pa_volume(int percent)
{
	int	vol;

	if (percent < 0)
		percent = 0;
	if (percent > 100)
		percent = 100;
	vol = (65536 * percent) / 100;
	return (vol);
}

void	start_music(t_game *cub)
{
	pid_t	pid;
	int		bg_percent;
	int		bg_volume;
	char	vol_str[16];

	if (cub->music_id != 0)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		bg_percent = cub->sound_level / 1.3;
		bg_volume = get_pa_volume(bg_percent);
		snprintf(vol_str, sizeof(vol_str), "%d", bg_volume);
		while (1)
		{
			execlp("paplay", "paplay", "--volume", vol_str,
				"bonus/src/music_bonus/paperchase.wav", NULL);
			sleep(1);
		}
		exit(1);
	}
	cub->music_id = pid;
}

void	stop_music(t_game *cub)
{
	if (cub->music_id <= 0)
		return ;
	kill(cub->music_id, SIGTERM);
	waitpid(cub->music_id, NULL, 0);
	cub->music_id = 0;
}
