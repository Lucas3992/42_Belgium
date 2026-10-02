/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:27 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/03 11:01:14 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *info, void *ctxt)
{
	int				bit;
	int				mask;
	static t_state	state;

	(void)ctxt;
	mask = 1 << state.index;
	bit = (sig == SIGUSR2);
	if (bit == 1)
		state.octet = state.octet | mask;
	state.index++;
	if (state.index == 8)
	{
		write(1, &state.octet, 1);
		state.octet = 0;
		state.index = 0;
	}
	if (info && info->si_pid)
		kill(info->si_pid, SIGUSR1);
}

static void	setup_signal(int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(sig, &sa, NULL) == -1)
		error();
}

int	main(void)
{
	ft_printf("PID : %d\n", getpid());
	setup_signal(SIGUSR1);
	setup_signal(SIGUSR2);
	while (1)
		pause();
	return (0);
}
