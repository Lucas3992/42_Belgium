/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:06:40 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/22 09:35:11 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//a modif pour le bonus
static void	check_unallowed_chars(char **map, t_game *game)
{
	int		x;
	int		y;
	char	t;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			t = map[y][x];
			if (t != 'P' && t != 'E' && t != 'C' && t != '1' && t != '0')
				explicit_error_and_exit("Detected invalid tile in map", game);
			x++;
		}
		y++;
	}
}

static void	count_pec(char **map, int *p, int *e, int *c)
{
	int	x;
	int	y;

	*p = 0;
	*e = 0;
	*c = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				(*p)++;
			else if (map[y][x] == 'E')
				(*e)++;
			else if (map[y][x] == 'C')
				(*c)++;
			x++;
		}
		y++;
	}
}

void	is_valid_pec(char **map, t_game *game)
{
	int	p;
	int	e;
	int	c;

	check_unallowed_chars(map, game);
	count_pec(map, &p, &e, &c);
	if (p != 1)
		explicit_error_and_exit("The game needs exactly 1 player", game);
	if (e != 1)
		explicit_error_and_exit("The game needs exactly 1 exit", game);
	if (c < 1)
		explicit_error_and_exit("The game needs at least 1 collectible", game);
	game->total_collectibles = c;
	game->remaining_collectibles = c;
}
