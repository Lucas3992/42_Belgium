/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:50:06 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/12 11:19:15 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleeping(t_philo *philo)
{
	log_state(philo, "is sleeping");
	smart_wait(philo->rules->time_to_sleep, philo->rules);
}

static void	thinking(t_philo *philo)
{
	log_state(philo, "is thinking");
	usleep(100);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(philo->rules->time_to_eat * 1000 / 2);
	while (!check_for_monitor_flag(philo->rules))
	{
		if (!eat(philo))
			break ;
		if (check_for_monitor_flag(philo->rules))
			break ;
		if (ate_enough(philo))
			break ;
		if (check_for_monitor_flag(philo->rules))
			break ;
		sleeping(philo);
		if (check_for_monitor_flag(philo->rules))
			break ;
		thinking(philo);
	}
	return (NULL);
}
