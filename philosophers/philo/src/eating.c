/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:16:59 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/12 11:53:11 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_left_first(t_philo *philo)
{
	if (philo->rules->nb_philos % 2 == 0)
		return (philo->id % 2 == 0);
	return (philo->id != philo->rules->nb_philos -1);
}

static int	take_forks(t_philo *philo, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	if (check_for_monitor_flag(philo->rules))
		return (0);
	pthread_mutex_lock(f1);
	log_state(philo, "has taken a fork");
	if (check_for_monitor_flag(philo->rules))
	{
		pthread_mutex_unlock(f1);
		return (0);
	}
	pthread_mutex_lock(f2);
	log_state(philo, "has taken a fork");
	if (check_for_monitor_flag(philo->rules))
	{
		pthread_mutex_unlock(f2);
		pthread_mutex_unlock(f1);
		return (0);
	}
	return (1);
}

static int	take_both_forks(t_philo *philo)
{
	if (check_for_monitor_flag(philo->rules) || philo->rules->nb_philos == 1)
		return (0);
	if (take_left_first(philo))
		return (take_forks(philo, philo->left_fork, philo->right_fork));
	else
		return (take_forks(philo, philo->right_fork, philo->left_fork));
}

static void	release_forks(t_philo *philo)
{
	if (take_left_first(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

int	eat(t_philo *philo)
{
	if (!take_both_forks(philo))
		return (0);
	update_last_meal(philo);
	log_state(philo, "is eating");
	smart_wait(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	release_forks(philo);
	return (1);
}
