/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:47:30 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/25 09:31:17 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_all_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	if (rules->monitor)
		pthread_join(rules->monitor, NULL);
}

static void	create_all_threads(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start_time = get_time_in_ms();
	while (i < rules->nb_philos)
	{
		if (pthread_create(&rules->philos[i].thread, NULL,
				philos_routine, &rules->philos[i]) != 0)
			clean_exit(rules, "Failed to create pthread");
		pthread_mutex_lock(&rules->philos[i].meals_mutex);
		rules->philos[i].last_meal = rules->start_time;
		pthread_mutex_unlock(&rules->philos[i].meals_mutex);
		i++;
	}
	if (pthread_create(&rules->monitor, NULL, monitor, rules) != 0)
		clean_exit(rules, "Failed to create monitor thread");
}

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (clean_exit(rules, "Malloc failed"), 1);
	ft_bzero(rules, sizeof(t_rules));
	parse_arg(ac, av, rules);
	init_rules(rules);
	create_all_threads(rules);
	join_all_threads(rules);
	free_struct(rules);
	return (0);
}
