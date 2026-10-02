/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:14 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 14:50:07 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_GT || token->type == T_DGT
		|| token->type == T_LT || token->type == T_DLT)
		return (1);
	return (0);
}

int	assign_redir(t_token *token, t_redir *new)
{
	if (!token || !new)
		return (0);
	if (is_redir(token))
	{
		if (token->type == T_GT)
			new->type = R_OUT;
		else if (token->type == T_LT)
			new->type = R_IN;
		else if (token->type == T_DGT)
			new->type = R_APP;
		else if (token->type == T_DLT)
			new->type = R_HDOC;
		return (1);
	}
	return (0);
}

void	add_redir_node(t_redir **first, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!new_redir)
		return ;
	if (!*first)
	{
		*first = new_redir;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

t_redir	*parse_one_redir(t_token **tokens)
{
	t_redir	*new;

	if (!tokens || !*tokens || !is_redir(*tokens))
		return (NULL);
	new = init_redir();
	if (!new)
		return (NULL);
	if (!assign_redir(*tokens, new))
		return (free_redir(new, NULL));
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != T_WORD || !(*tokens)->value)
		return (free_redir(new, (char *)which_token_error(*tokens)));
	if (new->type == R_HDOC)
	{
		if (!hdoc_limit(new, (*tokens)->value))
			return (free_redir(new, NULL));
	}
	else
	{
		if (!fill_redir_target(new, *tokens))
			return (free_redir(new, NULL));
	}
	*tokens = (*tokens)->next;
	return (new);
}

int	parse_redir(t_token **token, t_cmds *new)
{
	t_redir	*tmp;

	if (!token || !new)
		return (0);
	while (*token && is_redir(*token))
	{
		tmp = parse_one_redir(token);
		if (!tmp)
			return (0);
		add_redir_node(&new->redir, tmp);
	}
	return (1);
}
