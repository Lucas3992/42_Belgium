/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:25:29 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:48:37 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_unset_or_empty(t_shell *ms)
{
	t_var	*path;

	path = env_find_key(ms->env, "PATH");
	if (!path || !path->has_eq || !path->value || path->value[0] == '\0')
		return (1);
	return (0);
}

void	if_no_path(char *name, t_shell *ms, int *error_code)
{
	*error_code = 127;
	if (path_unset_or_empty(ms))
	{
		if (access(name, F_OK) == 0)
		{
			if (is_directory(name))
				*error_code = 126;
			else if (access(name, X_OK) != 0)
				*error_code = 126;
		}
	}
}

void	close_fd_redirect(int *fd_in, int *fd_out)
{
	if (*fd_in >= 0)
		close(*fd_in);
	if (*fd_out >= 0)
		close(*fd_out);
	*fd_in = -1;
	*fd_out = -1;
}

int	do_redirects_and_dup(t_exec *ex, t_cmds *cmd)
{
	int	status;

	status = redirect(ex->ms, cmd, &ex->fd_in, &ex->fd_out);
	if (status != 0)
	{
		close_fd_redirect(&ex->fd_in, &ex->fd_out);
		return (1);
	}
	if (dup_fds_if_needed(ex) != 0)
	{
		close_fd_redirect(&ex->fd_in, &ex->fd_out);
		return (1);
	}
	close_fd_redirect(&ex->fd_in, &ex->fd_out);
	return (0);
}
