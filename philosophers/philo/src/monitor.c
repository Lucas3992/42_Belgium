/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:51:21 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/12 11:46:00 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_are_done_eating(t_rules *rules)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (rules->meals_required != -1)
	{
		while (i < rules->nb_philos)
		{
			pthread_mutex_lock(&rules->philos[i].meals_mutex);
			if (rules->philos[i].meals_eaten == rules->meals_required)
				count++;
			pthread_mutex_unlock(&rules->philos[i].meals_mutex);
			i++;
		}
		if (count == rules->nb_philos)
			return (1);
	}
	return (0);
}

static int	philo_i_died(t_rules *rules)
{
	int		i;
	long	now;

	i = 0;
	while (i < rules->nb_philos)
	{
		pthread_mutex_lock(&rules->philos[i].meals_mutex);
		now = get_time_in_ms();
		if (now - rules->philos[i].last_meal > rules->time_to_die)
		{
			pthread_mutex_unlock(&rules->philos[i].meals_mutex);
			return (i +1);
		}
		pthread_mutex_unlock(&rules->philos[i].meals_mutex);
		i++;
	}
	return (-1);
}

void	*monitor(void *arg)
{
	t_rules	*rules;
	int		dead_philo;
	long	timestamp;

	rules = arg;
	while (1)
	{
		dead_philo = philo_i_died(rules);
		if (dead_philo != -1)
		{
			set_simulation_end(rules);
			pthread_mutex_lock(&rules->print_mutex);
			timestamp = get_time_in_ms() - rules->start_time;
			printf("%ld %d has died\n", timestamp, dead_philo);
			pthread_mutex_unlock(&rules->print_mutex);
			return (NULL);
		}
		else if (all_philos_are_done_eating(rules))
		{
			set_simulation_end(rules);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
