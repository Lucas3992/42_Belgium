/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_hdoc_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:47:44 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/21 12:47:51 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hdoc_handle_interrupt(t_hdoc *doc, t_shell *ms)
{
	close(doc->p[1]);
	close(doc->p[0]);
	hdoc_restore_stdin(doc);
	setup_signals_interactive();
	ms->last_exit_code = 130;
	return (1);
}

static int	hdoc_handle_error(t_hdoc *doc)
{
	hdoc_restore_stdin(doc);
	setup_signals_interactive();
	close(doc->p[0]);
	close(doc->p[1]);
	return (1);
}

static int	hdoc_finalize(t_hdoc *doc, t_redir *redir, int *fd_in)
{
	if (doc->saw_eof && !doc->saw_delim)
		hdoc_warn_eof(redir->target);
	close(doc->p[1]);
	if (hdoc_restore_stdin(doc))
	{
		close(doc->p[0]);
		setup_signals_interactive();
		return (1);
	}
	setup_signals_interactive();
	*fd_in = doc->p[0];
	return (0);
}

int	redirect_hdoc(t_shell *ms, t_redir *redir, int *fd_in)
{
	t_hdoc	doc;

	if (*fd_in >= 0)
		close(*fd_in);
	if (hdoc_open(&doc))
		return (1);
	setup_signals_heredoc();
	if (hdoc_read_loop(ms, redir, &doc))
		return (hdoc_handle_error(&doc));
	if (g_sig == 130)
		return (hdoc_handle_interrupt(&doc, ms));
	return (hdoc_finalize(&doc, redir, fd_in));
}
