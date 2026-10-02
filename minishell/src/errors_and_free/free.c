/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:08 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 11:05:05 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_words_tail(char **words, int i, int size)
{
	while (i < size)
	{
		free(words[i]);
		i++;
	}
}

void	*free_redir(t_redir *redir, char *msg)
{
	t_redir	*next;

	if (msg)
		msg_error(msg, NULL, NULL, 0);
	while (redir)
	{
		next = redir->next;
		if (redir->target)
			free(redir->target);
		if (redir->raw)
			free(redir->raw);
		free(redir);
		redir = next;
	}
	return (NULL);
}

void	free_cmd_list(t_cmds *list)
{
	if (!list)
		return ;
	if (list->args)
		free_array(list->args);
	if (list->redir)
		free_redir(list->redir, NULL);
	if (list->path)
		free(list->path);
	free(list);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	if (ast->type == CMD_NODE && ast->cmd)
		free_cmd_list(ast->cmd);
	free(ast);
}
