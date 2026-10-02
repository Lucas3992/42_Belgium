/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:30:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 14:23:57 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_cmd(t_exec *ex, t_cmds *cmd)
{
	if (save_stdio(ex) != 0)
		return (cleanup(ex, 1));
	if (apply_carry_fdin(ex) != 0)
		return (cleanup(ex, 1));
	if (redirect(ex->ms, cmd, &ex->fd_in, &ex->fd_out))
		return (cleanup(ex, 1));
	return (cleanup(ex, 0));
}

static void	if_onetwoseven(t_shell *ms, int check, char *name)
{
	if (check)
		print_no_such_file(name);
	else if (path_unset_or_empty(ms))
	{
		if (is_directory(name))
			print_is_directory(name);
		else
			print_no_such_file(name);
	}
	else
		print_cmd_not_found(name);
}

static void	msg_unset(t_shell *ms)
{
	if (path_unset_or_empty(ms))
		ft_puterr("minishell: : No such file or directory\n");
	else
		ft_puterr("minishell: '' : command not found\n");
}

int	print_resolve_error_set_error_code(t_exec *ex, char *name, int error_code)
{
	int	check;

	check = 0;
	if (!name || name[0] == '\0')
	{
		ex->ms->last_exit_code = 127;
		msg_unset(ex->ms);
		return (ex->ms->last_exit_code);
	}
	check = has_slash(name);
	if (error_code == 127)
	{
		if_onetwoseven(ex->ms, check, name);
		if (path_unset_or_empty(ex->ms) && is_directory(name))
			error_code = 126;
	}
	else if (error_code == 126)
	{
		if (is_directory(name))
			print_is_directory(name);
		else
			print_permission_denied(name);
	}
	ex->ms->last_exit_code = error_code;
	return (error_code);
}

int	resolve_or_report(t_exec *ex, t_cmds *cmd)
{
	int		error_code;
	char	*path;

	if (cmd && cmd->builtin)
		return (0);
	error_code = 0;
	path = NULL;
	path = resolve_command_path(ex->ms, cmd, &error_code);
	if (!path)
	{
		print_resolve_error_set_error_code(ex, cmd->args[0], error_code);
		ex->ms->last_exit_code = error_code;
		return (error_code);
	}
	cmd->path = path;
	return (0);
}
