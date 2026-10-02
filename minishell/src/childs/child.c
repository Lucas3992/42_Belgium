/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:48:39 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/21 12:48:43 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:18 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 14:46:19by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	core_dumped(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		else if (sig == SIGINT)
			write(1, "\n", 1);
	}
}

static int	wait_error(void)
{
	if (errno == EINTR)
		return (1);
	if (errno != ECHILD)
		perror("Waitpid");
	return (0);
}

void	wait_childs(t_exec *exec, t_shell *ms)
{
	int		status;
	pid_t	last_child;
	pid_t	pid;
	int		waited;

	if (!exec || exec->index <= 0)
		return ;
	last_child = exec->child[exec->index - 1];
	if (exec->last_pid != -1)
		last_child = exec->last_pid;
	waited = 0;
	while (waited < exec->index)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			if (wait_error())
				continue ;
			break ;
		}
		waited++;
		if (pid == last_child)
			ms->last_exit_code = get_error_code(status);
		core_dumped(status);
	}
}
