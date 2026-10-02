/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:54 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:57:55 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

static void	firing(t_game *game, t_weapon *wp, int left, long long ct)
{
	wp->is_firing = 1;
	wp->fire_frame = 0;
	game->player.last_fire_time = ct;
	if (left == 1)
		game->player.last_weapon = 1;
	else
		game->player.last_weapon = 0;
	shoot(game);
	play_random_sound(game);
}

void	fire_weapon(t_game *game)
{
	long long	current_time;
	long long	time_since_last_fire;

	current_time = get_current_time_ms();
	time_since_last_fire = current_time - game->player.last_fire_time;
	if (time_since_last_fire < game->player.fire_rate)
		return ;
	if (game->player.last_weapon == 0)
	{
		if (!game->player.weapon_left->is_firing)
			firing(game, game->player.weapon_left, 1, current_time);
	}
	else
	{
		if (!game->player.weapon_right->is_firing)
			firing(game, game->player.weapon_right, 0, current_time);
	}
}

void	init_weapon(t_game *game)
{
	game->player.weapon_right = malloc(sizeof(t_weapon));
	if (!game->player.weapon_right)
	{
		printf("Error: Cannot allocate right weapon\n");
		exit(1);
	}
	load_weapon(game, game->player.weapon_right,
		"textures/idle.xpm", "textures/fire.xpm");
	game->player.weapon_left = malloc(sizeof(t_weapon));
	if (!game->player.weapon_left)
	{
		printf("Error: Cannot allocate left weapon\n");
		exit(1);
	}
	load_weapon(game, game->player.weapon_left,
		"textures/idle_left.xpm", "textures/fire_left.xpm");
	game->player.last_weapon = 1;
	game->player.last_fire_time = 0;
	game->player.fire_rate = 1000;
}
