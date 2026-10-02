/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:49 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 12:12:10 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_shell *ms, t_cmds *current, int *fd_in, int *fd_out)
{
	t_redir	*current_redir;
	int		status;

	status = 0;
	current_redir = current->redir;
	if (!current_redir)
		return (0);
	while (current_redir)
	{
		status = redirect_choice(ms, current_redir, fd_in, fd_out);
		if (status != 0)
		{
			close_fd_redirect(fd_in, fd_out);
			ms->last_exit_code = 1;
			return (1);
		}
		current_redir = current_redir->next;
	}
	return (0);
}
