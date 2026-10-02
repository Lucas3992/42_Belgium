/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_choices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:43 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:37:31 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_redir *redirect, int *fd_in)
{
	if (*fd_in >= 0)
		close(*fd_in);
	*fd_in = open(redirect->target, O_RDONLY);
	if (*fd_in < 0)
	{
		msg_error(NULL, redirect->target, ": No such file or directory", 1);
		return (1);
	}
	return (0);
}

int	redirect_out(t_redir *redirect, int *fd_out)
{
	if (*fd_out >= 0)
		close(*fd_out);
	*fd_out = open(redirect->target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (*fd_out < 0)
	{
		msg_error(NULL, redirect->target, ": No such file or directory", 1);
		return (1);
	}
	return (0);
}

int	redirect_app(t_redir *redirect, int *fd_out)
{
	if (*fd_out >= 0)
		close(*fd_out);
	*fd_out = open(redirect->target, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (*fd_out < 0)
	{
		msg_error(NULL, redirect->target, ": No such file or directory", 1);
		return (1);
	}
	return (0);
}

int	redirect_choice(t_shell *ms, t_redir *r, int *fd_in, int *fd_out)
{
	const char	*shown;
	int			status;

	status = 0;
	if (r->type == R_IN || r->type == R_OUT || r->type == R_APP)
	{
		shown = r->raw;
		if (!shown)
			shown = r->target;
		if (validate_redirect_target(shown, &r->target))
			return (1);
		return (ms->last_exit_code = open_file_redir(r, fd_in, fd_out));
	}
	if (r->type == R_HDOC)
	{
		if (r->hdoc_fd < 0)
			return (1);
		if (*fd_in >= 0)
			close(*fd_in);
		*fd_in = r->hdoc_fd;
		r->hdoc_fd = -1;
	}
	ms->last_exit_code = status;
	return (status);
}
