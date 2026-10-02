/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:07:37 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/22 11:43:48 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atol(const char *str)
{
	size_t		i;
	int			sign;
	long long	nb;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (sign * nb);
}

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
	return (s);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			tv_in_ms;

	gettimeofday(&tv, NULL);
	tv_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (tv_in_ms);
}

void	smart_wait(long ms, t_rules *rules)
{
	long	start;
	long	now;

	start = get_time_in_ms();
	while (!check_for_monitor_flag(rules))
	{
		now = get_time_in_ms();
		if (now - start >= ms)
			break ;
		usleep(500);
	}
}

void	log_state(t_philo *philo, char *msg)
{
	long	timestamp;

	if (check_for_monitor_flag(philo->rules))
		return ;
	pthread_mutex_lock(&philo->rules->print_mutex);
	timestamp = get_time_in_ms() - philo->rules->start_time;
	if (!check_for_monitor_flag(philo->rules))
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}
