/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:09:57 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/25 09:59:04 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutex(t_rules *rules)
{
	int	i;

	if (rules->philos)
	{
		i = 0;
		while (i < rules->nb_philos)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			pthread_mutex_destroy(&rules->philos[i].meals_mutex);
			i++;
		}
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->simulation_mutex);
	free(rules->forks);
	rules->forks = NULL;
	free(rules->philos);
	rules->philos = NULL;
}

void	free_struct(t_rules *rules)
{
	if (!rules)
		return ;
	destroy_all_mutex(rules);
	free(rules);
}

void	clean_exit(t_rules *rules, char *msg)
{
	if (rules)
		free_struct(rules);
	if (!msg)
		return ;
	printf("Error:\n%s\n", msg);
	exit(1);
}
