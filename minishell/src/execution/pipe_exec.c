/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:57 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:11:55 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_child(t_exec *ex, int p[2])
{
	set_child_signals();
	dup2(p[1], STDOUT_FILENO);
	close_pipe(p);
	if (ex->carry_fd >= 0)
	{
		dup2(ex->carry_fd, STDIN_FILENO);
		close(ex->carry_fd);
		ex->carry_fd = -1;
	}
	ex->in_pipe = true;
}

static void	after_fork(t_exec *ex, pid_t pid, int p[2])
{
	ex->child[ex->index] = pid;
	ex->index++;
	close(p[1]);
	if (ex->carry_fd >= 0)
		close(ex->carry_fd);
	ex->carry_fd = p[0];
	ex->in_pipe = true;
}

static void	exec_left_direct(t_exec *ex, t_ast *tree)
{
	char	**envp;
	t_cmds	*cmd;

	if (!tree || tree->type != CMD_NODE || !tree->cmd)
		exit(1);
	cmd = tree->cmd;
	ex->fd_in = -1;
	ex->fd_out = -1;
	if (do_redirects_and_dup(ex, cmd) != 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->builtin)
		exit(exec_builtin(tree, ex->ms, 1));
	resolve_or_report(ex, cmd);
	if (!cmd->path)
		exit(ex->ms->last_exit_code);
	envp = var_to_env(ex->ms);
	execve(cmd->path, cmd->args, envp);
	if (errno == ENOEXEC)
		execve("/bin/sh", (char *[]){"sh", cmd->path, NULL}, envp);
	free_array(envp);
	if (errno == EACCES || errno == EPERM || errno == EISDIR)
		exit(126);
	exit(127);
}

void	in_left_child( t_exec *ex, t_ast *tree, int p[2])
{
	left_child(ex, p);
	if (tree->left && tree->left->type == PIPE_NODE)
		exit(exec_branch(tree->left, ex));
	exec_left_direct(ex, tree->left);
	exit(1);
}

int	pipe_exec(t_ast *tree, t_exec *ex)
{
	int		p[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(p) != 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (close_pipe(p), 1);
	if (pid == 0)
		in_left_child(ex, tree, p);
	after_fork(ex, pid, p);
	status = exec_branch(tree->right, ex);
	if (ex->carry_fd >= 0)
	{
		close(ex->carry_fd);
		ex->carry_fd = -1;
	}
	return (status);
}
