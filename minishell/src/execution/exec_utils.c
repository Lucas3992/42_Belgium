/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:49 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 12:51:01 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int *p)
{
	close(p[0]);
	close(p[1]);
}

int	save_stdio(t_exec *ex)
{
	if (ex->s_stdin != -1 || ex->s_stdout != -1)
		return (0);
	ex->s_stdin = dup(STDIN_FILENO);
	if (ex->s_stdin < 0)
		return (1);
	ex->s_stdout = dup(STDOUT_FILENO);
	if (ex->s_stdout < 0)
	{
		close(ex->s_stdin);
		ex->s_stdin = -1;
		return (1);
	}
	return (0);
}

int	restore_stdio(t_exec *ex)
{
	if (ex->s_stdin != -1)
	{
		if (dup2(ex->s_stdin, STDIN_FILENO) == -1)
			return (1);
		close(ex->s_stdin);
		ex->s_stdin = -1;
	}
	if (ex->s_stdout != -1)
	{
		if (dup2(ex->s_stdout, STDOUT_FILENO) == -1)
			return (1);
		close(ex->s_stdout);
		ex->s_stdout = -1;
	}
	return (0);
}

int	apply_carry_fdin(t_exec *ex)
{
	if (ex->carry_fd >= 0)
	{
		if (dup2(ex->carry_fd, STDIN_FILENO) == -1)
		{
			close(ex->carry_fd);
			ex->carry_fd = -1;
			return (1);
		}
		close(ex->carry_fd);
		ex->carry_fd = -1;
	}
	return (0);
}

int	safe_dup2_close(int from, int to)
{
	if (from >= 0 && from != to)
	{
		if (dup2(from, to) == -1)
			return (1);
		close(from);
	}
	return (0);
}
