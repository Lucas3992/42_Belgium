/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_sounds_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:15 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:16 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	play_sfx(const char *path, int percent)
{
	pid_t	pid;
	int		vol;
	char	vol_str[16];

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		vol = get_pa_volume(percent);
		snprintf(vol_str, sizeof(vol_str), "%d", vol);
		execlp("paplay", "paplay",
			"--volume", vol_str, path, NULL);
		perror("execlp failed");
		_exit(1);
	}
}

static void	start_brbrbr(t_game *cub)
{
	play_sfx("bonus/src/music_bonus/brbrbr.wav", cub->sound_level);
}

static void	start_plc(t_game *cub)
{
	play_sfx("bonus/src/music_bonus/peter-leur-chevilles.wav",
		cub->sound_level);
}

void	play_random_sound(t_game *cub)
{
	int	random;

	random = ft_math_random(0, 1);
	if (random == 0)
		start_brbrbr(cub);
	else
		start_plc(cub);
}
