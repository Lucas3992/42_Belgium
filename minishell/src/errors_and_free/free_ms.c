/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:04 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 12:16:26 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *first)
{
	t_token	*tmp;

	while (first)
	{
		tmp = first->next;
		if (first->value)
			free(first->value);
		if (first->raw)
			free(first->raw);
		free(first);
		first = tmp;
	}
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->child)
		free(exec->child);
	free(exec);
	exec = NULL;
}

void	free_ms(t_shell *ms, t_token *tokens)
{
	if (!ms)
		return ;
	if (tokens)
		free_tokens(tokens);
	if (ms->tree)
		free_ast(ms->tree);
	if (ms->env)
		free_var_list(&ms->env);
	rl_clear_history();
}
