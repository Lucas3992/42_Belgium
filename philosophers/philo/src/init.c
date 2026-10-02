/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:19:05 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/25 09:40:47 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philos);
	if (!rules->forks)
		return (0);
	i = 0;
	while (i < rules->nb_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	init_philos(t_rules *rules)
{
	int	i;

	rules->philos = malloc(sizeof(t_philo) * rules->nb_philos);
	if (!rules->philos)
		return (0);
	i = 0;
	while (i < rules->nb_philos)
	{
		rules->philos[i].id = i +1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i +1) % rules->nb_philos];
		rules->philos[i].last_meal = rules->start_time;
		if (pthread_mutex_init(&rules->philos[i].meals_mutex, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_rules(t_rules *rules)
{
	if (!init_forks(rules))
		clean_exit(rules, "Failed to init forks");
	rules->simulation_over = 0;
	if (!init_philos(rules))
		clean_exit(rules, "Failed to init philos");
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0
		|| pthread_mutex_init(&rules->simulation_mutex, NULL) != 0)
		clean_exit(rules, "Failed to init mutex");
}
