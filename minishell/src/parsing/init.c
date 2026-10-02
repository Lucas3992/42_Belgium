/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:54 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/17 10:24:55 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*init_redir(void)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = -1;
	new->target = NULL;
	new->next = NULL;
	new->hdoc_quoted = 0;
	new->hdoc_fd = -1;
	new->raw = NULL;
	return (new);
}

t_cmds	*init_cmd(void)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redir = NULL;
	new->path = NULL;
	new->builtin = false;
	new->type = 0;
	return (new);
}

t_ast	*create_ast_cmd(t_cmds *cmd)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = CMD_NODE;
	new->cmd = cmd;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*create_ast_pipe(t_ast *left, t_ast *right)
{
	t_ast	*new;

	if (!left || !right)
		return (NULL);
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = PIPE_NODE;
	new->cmd = NULL;
	new->left = left;
	new->right = right;
	return (new);
}

void	init_exp(t_exp *new, t_shell *ms, char *in)
{
	if (in)
		new->in = in;
	else
		new->in = "";
	new->current = NULL;
	new->out = NULL;
	new->i = 0;
	new->sq = 0;
	new->dq = 0;
	new->quote_flag = 0;
	new->out_len = 0;
	new->env = ms->env;
	new->last_status = ms->last_exit_code;
}
