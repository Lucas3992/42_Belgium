/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:54 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 11:43:19 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_cmds(t_ast *tree, t_shell *ms)
{
	size_t	count;

	count = 0;
	if (!tree)
		return (0);
	if (tree->type == CMD_NODE)
	{
		is_builtin(ms, tree->cmd);
		return (1);
	}
	if (tree->type == PIPE_NODE)
		return (count_cmds(tree->left, ms) + count_cmds(tree->right, ms));
	return (count);
}

static void	exec_init(t_exec *ex, t_shell *ms)
{
	ex->child = NULL;
	ex->ms = ms;
	ex->n_cmds = count_cmds(ms->tree, ms);
	ex->index = 0;
	ex->last_pid = -1;
	ex->in_pipe = false;
	ex->pipe_i = 0;
	ex->carry_fd = -1;
	ex->s_stdin = -1;
	ex->s_stdout = -1;
	if (ex->n_cmds == 0)
		return ;
	ex->child = malloc(sizeof(pid_t) * ex->n_cmds);
	if (!ex->child)
		msg_error("Child not made", NULL, NULL, 1);
	if (ex->n_cmds == 1 && ms->tree->type == CMD_NODE
		&& ms->tree->cmd && ms->tree->cmd->builtin)
		ex->parent_exec = true;
	else
		ex->parent_exec = false;
}

static int	safe_carry(int *carry_fd)
{
	if (*carry_fd >= 0)
	{
		close(*carry_fd);
		*carry_fd = -1;
	}
	return (0);
}

int	exec_branch(t_ast *tree, t_exec *ex)
{
	int	status;

	status = 0;
	if (tree == NULL)
		return (safe_carry(&ex->carry_fd));
	if (tree->type == PIPE_NODE)
		status = pipe_exec(tree, ex);
	else if (tree->type == CMD_NODE)
		status = cmd_exec(tree, ex);
	else
		status = safe_carry(&ex->carry_fd);
	return (status);
}

int	exec(t_shell *ms)
{
	t_exec	*ex;
	int		status;

	ex = malloc(sizeof(t_exec));
	if (!ex)
		return (msg_error("exec failed", NULL, NULL, 1));
	exec_init(ex, ms);
	if (ex->n_cmds == 0)
	{
		free_exec(ex);
		return (0);
	}
	status = exec_branch(ms->tree, ex);
	if (!ex->parent_exec)
	{
		setup_signals_interactive();
		wait_childs(ex, ms);
	}
	close_all_heredocs_from_ast(ms->tree);
	setup_signals();
	restore_stdio(ex);
	free_exec(ex);
	return (status);
}
