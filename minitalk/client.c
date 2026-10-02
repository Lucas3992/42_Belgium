/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:57:51 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/03 11:02:08 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

pid_t	parsing_pid(char *str)
{
	pid_t	pid;
	int		i;

	if (!str || str[0] == '\0')
		return (-1);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	pid = (pid_t)ft_atoi(str);
	if (pid <= 0)
		return (-1);
	return (pid);
}

static void	send_octet(unsigned char octet, pid_t pid)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = (octet >> i) & 1;
		if (bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
		while (!g_ack)
			pause();
		g_ack = 0;
		i++;
	}
}

static void	send_message_to_serv(unsigned char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_octet(str[i], pid);
		i++;
	}
	send_octet('\0', pid);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sa;

	if (ac != 3)
		error();
	else
	{
		pid = parsing_pid(av[1]);
		if (pid == -1)
			error();
		if (kill(pid, 0) == -1)
			error();
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = ack_handler;
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGUSR1, &sa, NULL) == -1)
			error();
		send_message_to_serv((unsigned char *)av[2], pid);
	}
	return (0);
}
