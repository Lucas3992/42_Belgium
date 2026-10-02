/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:39 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:38:41 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_hdoc_cmd(t_shell *ms, t_cmds *cmd)
{
	t_redir	*red;
	int		fd;

	red = cmd->redir;
	while (red)
	{
		if (red->type == R_HDOC)
		{
			fd = -1;
			if (redirect_hdoc(ms, red, &fd))
				return (1);
			if (g_sig == 130)
				return (1);
			red->hdoc_fd = fd;
		}
		red = red->next;
	}
	return (0);
}

static int	prepare_hdoc_tree(t_shell *ms, t_ast *tree)
{
	if (!tree)
		return (0);
	if (tree->type == CMD_NODE && tree->cmd)
	{
		if (prepare_hdoc_cmd(ms, tree->cmd))
			return (1);
		if (g_sig == 130)
			return (1);
	}
	if (prepare_hdoc_tree(ms, tree->left))
		return (1);
	if (g_sig == 130)
		return (1);
	if (prepare_hdoc_tree(ms, tree->right))
		return (1);
	return (0);
}

void	close_all_heredocs(t_cmds *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == R_HDOC && r->hdoc_fd >= 0)
		{
			close(r->hdoc_fd);
			r->hdoc_fd = -1;
		}
		r = r->next;
	}
}

void	close_all_heredocs_from_ast(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->type == CMD_NODE && tree->cmd)
		close_all_heredocs(tree->cmd);
	close_all_heredocs_from_ast(tree->left);
	close_all_heredocs_from_ast(tree->right);
}

int	prepare_all_heredocs(t_shell *ms)
{
	int	interrupted;

	interrupted = prepare_hdoc_tree(ms, ms->tree);
	if (interrupted)
	{
		close_all_heredocs_from_ast(ms->tree);
		free_ast(ms->tree);
		ms->tree = NULL;
		ms->last_exit_code = 130;
		g_sig = 0;
		return (0);
	}
	return (1);
}
