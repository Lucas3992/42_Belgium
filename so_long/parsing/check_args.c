/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:46:01 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 12:09:09 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	argc_equals_two(int argc, t_game *game)
{
	if (argc == 2)
		return (1);
	else
	{
		explicit_error_and_exit("The program needs exactly 2 arguments", game);
		return (0);
	}
}

static int	check_extension(char *str, t_game *game)
{
	int	i;
	int	size;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	size = i;
	if (size >= 4 && str[size -1] == 'r' && str[size -2] == 'e'
		&& str[size -3] == 'b' && str[size -4] == '.')
		return (1);
	else
	{
		explicit_error_and_exit("Wrong extension for the map", game);
		return (0);
	}
}

int	arguments_are_valid(int argc, char *argv, t_game *game)
{
	if (argc_equals_two(argc, game) && check_extension(argv, game))
		return (1);
	else
		return (0);
}
