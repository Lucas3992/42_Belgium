/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:29:37 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/12 09:35:02 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_last_meal(t_philo *philo)
{
	long	now;

	now = get_time_in_ms();
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal = now;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void	set_simulation_end(t_rules *rules)
{
	pthread_mutex_lock(&rules->simulation_mutex);
	rules->simulation_over = 1;
	pthread_mutex_unlock(&rules->simulation_mutex);
}

int	check_for_monitor_flag(t_rules *rules)
{
	int	monitor_tells_to_stop;

	pthread_mutex_lock(&rules->simulation_mutex);
	monitor_tells_to_stop = rules->simulation_over;
	pthread_mutex_unlock(&rules->simulation_mutex);
	return (monitor_tells_to_stop);
}

int	ate_enough(t_philo *philo)
{
	int	done;

	if (philo->rules->meals_required == -1)
		return (0);
	pthread_mutex_lock(&philo->meals_mutex);
	done = (philo->meals_eaten == philo->rules->meals_required);
	pthread_mutex_unlock(&philo->meals_mutex);
	return (done);
}
