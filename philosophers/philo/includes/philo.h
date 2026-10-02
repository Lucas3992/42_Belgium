/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:41:46 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/08/12 12:45:38 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_mutex;
	pthread_t		thread;
	struct s_rules	*rules;
	int				id;
	int				meals_eaten;
	long			last_meal;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simulation_mutex;	
	pthread_t		monitor;
	t_philo			*philos;
	int				simulation_over;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long			start_time;
}					t_rules;

long long	ft_atol(const char *str);
void		log_state(t_philo *philo, char *msg);
void		*ft_bzero(void *s, size_t n);
void		smart_wait(long ms, t_rules *rules);
long		get_time_in_ms(void);

void		parse_arg(int ac, char **av, t_rules *rules);
void		init_rules(t_rules *rules);

int			ate_enough(t_philo *philo);
int			check_for_monitor_flag(t_rules *rules);
void		set_simulation_end(t_rules *rules);
void		update_last_meal(t_philo *philo);

int			eat(t_philo *philo);

void		*monitor(void *arg);
void		*philos_routine(void *arg);

void		free_struct(t_rules *rules);
void		clean_exit(t_rules *rules, char *msg);

#endif