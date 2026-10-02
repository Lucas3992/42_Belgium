/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:34 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:47:27 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hdoc_open(t_hdoc *doc)
{
	int	status;

	status = pipe(doc->p);
	if (status != 0)
		return (1);
	doc->saved = dup(STDIN_FILENO);
	doc->saw_delim = 0;
	doc->saw_eof = 0;
	if (doc->saved < 0)
		return (1);
	return (0);
}

int	hdoc_restore_stdin(t_hdoc *doc)
{
	int	ok;

	ok = dup2(doc->saved, STDIN_FILENO);
	close(doc->saved);
	if (ok < 0)
		return (1);
	return (0);
}

void	hdoc_warn_eof(const char *wanted)
{
	write(2, "minishell: warning: here-document at line 1 ", 44);
	write(2, "delimited by end-of-file (wanted `", 34);
	if (wanted)
		write(2, wanted, ft_strlen(wanted));
	write(2, "')\n", 3);
}

int	hdoc_read_loop(t_shell *ms, t_redir *redir, t_hdoc *doc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_sig == 130)
				return (0);
			doc->saw_eof = 1;
			return (0);
		}
		if (hdoc_stop(line, redir))
		{
			doc->saw_delim = 1 ;
			return (0);
		}
		inside_hdoc(ms, &line, redir, doc->p[1]);
		free(line);
	}
	return (0);
}
