/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:52:54 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/22 11:45:35 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_are_valid_int(t_rules *rules)
{
	if (!rules)
		return (0);
	if ((rules->time_to_die < 1 || rules->time_to_die > INT_MAX)
		|| (rules->time_to_eat < 1 || rules->time_to_eat > INT_MAX)
		|| (rules->time_to_sleep < 1 || rules->time_to_sleep > INT_MAX)
		|| (rules->nb_philos < 1))
		return (0);
	return (1);
}

static void	parse_four_args(t_rules *rules, char **av)
{
	rules->nb_philos = ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
}

static void	parse_five_args(t_rules *rules, char **av)
{
	rules->nb_philos = ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	rules->meals_required = ft_atol(av[5]);
}

void	parse_arg(int ac, char **av, t_rules *rules)
{
	if (ac != 5 && ac != 6)
		clean_exit(rules, "The program needs 4 or 5 arguments");
	if (ac == 5)
	{
		parse_four_args(rules, av);
		rules->meals_required = -1;
	}
	else if (ac == 6)
		parse_five_args(rules, av);
	if (!args_are_valid_int(rules)
		|| (rules->meals_required < 1 && rules->meals_required != -1))
		clean_exit(rules, "All arguments must be positive integers above 1");
	if (rules->nb_philos > 200)
		clean_exit(rules, "Max number of philos is 200");
}
