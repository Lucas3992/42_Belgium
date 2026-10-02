/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:45:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 11:19:53 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	update_last_ms_exit_code(t_shell *ms)
{
	if (g_sig != 0)
	{
		ms->last_exit_code = g_sig;
		g_sig = 0;
	}
	return (ms->last_exit_code);
}
