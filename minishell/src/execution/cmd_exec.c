/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:45 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:01:42 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_fds_if_needed(t_exec *ex)
{
	if (ex->fd_in >= 0 && dup2(ex->fd_in, STDIN_FILENO) == -1)
		return (1);
	if (ex->fd_out >= 0 && dup2(ex->fd_out, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

static int	builtin_parent_exec(t_exec *ex, t_ast *tree)
{
	int	status;

	if (save_stdio(ex) != 0)
		return (cleanup(ex, 1));
	if (apply_carry_fdin(ex) != 0)
		return (cleanup(ex, 1));
	if (redirect(ex->ms, tree->cmd, &ex->fd_in, &ex->fd_out) != 0)
		return (cleanup(ex, 1));
	if (dup_fds_if_needed(ex) != 0)
		return (cleanup(ex, 1));
	status = exec_builtin(tree, ex->ms, ex->in_pipe);
	return (cleanup(ex, status));
}

static void	child_exec_exit(t_exec *ex, t_ast *tree)
{
	char	**envp;

	set_child_signals();
	apply_carry_fdin(ex);
	if (do_redirects_and_dup(ex, tree->cmd) != 0)
		exit(1);
	if (tree->cmd->builtin)
		exit(exec_builtin(tree, ex->ms, ex->in_pipe));
	if (!tree->cmd->path)
		exit(ex->ms->last_exit_code);
	envp = var_to_env(ex->ms);
	execve(tree->cmd->path, tree->cmd->args, envp);
	if (errno == ENOEXEC)
		execve("/bin/sh", (char *[]){"sh", tree->cmd->path, NULL}, envp);
	free_array(envp);
	if (errno == EACCES || errno == EPERM || errno == EISDIR)
		exit(126);
	exit(127);
}

static int	spawn_cmd_child(t_exec *ex, t_ast *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		child_exec_exit(ex, tree);
	ex->child[ex->index] = pid;
	ex->last_pid = pid;
	ex->index++;
	close_all_heredocs_from_ast(tree);
	if (ex->carry_fd >= 0)
		close(ex->carry_fd);
	return (0);
}

int	cmd_exec(t_ast *tree, t_exec *ex)
{
	t_cmds	*cmd;

	cmd = tree->cmd;
	ex->fd_in = -1;
	ex->fd_out = -1;
	if (!cmd->args || !cmd->args[0])
		return (handle_empty_cmd(ex, cmd));
	if (cmd->builtin && ex->in_pipe == false)
		return (builtin_parent_exec(ex, tree));
	resolve_or_report(ex, cmd);
	return (spawn_cmd_child(ex, tree));
}
