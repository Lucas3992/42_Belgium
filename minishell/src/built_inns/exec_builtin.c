/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:40:45 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 10:10:00 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_ast *tree, t_shell *ms, int in_p)
{
	if (tree->cmd->type == T_ECHO)
		return (echo(tree->cmd->args));
	else if (tree->cmd->type == T_CD)
		return (cd(tree->cmd->args, ms));
	else if (tree->cmd->type == T_ENV)
		return (env_cmd(tree->cmd->args, ms));
	else if (tree->cmd->type == T_EXIT)
		return (exit_ms(tree->cmd->args, in_p, ms));
	else if (tree->cmd->type == T_EXPORT)
		return (export(tree->cmd->args, ms));
	else if (tree->cmd->type == T_PWD)
		return (pwd(ms));
	else if (tree->cmd->type == T_UNSET)
		return (unset(tree->cmd->args, ms));
	else if (tree->cmd->type == T_DOT)
		return (dot(tree->cmd->args));
	else
		return (1);
}
