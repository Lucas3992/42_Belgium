/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:25 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 14:34:50 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_word_token(char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		if (value)
			free(value);
		return (NULL);
	}
	token->type = T_WORD;
	token->value = value;
	token->raw = ft_strdup(value);
	token->next = NULL;
	return (token);
}

t_token	*create_op_token(t_token_type t_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = t_type;
	token->value = NULL;
	token->raw = NULL;
	token->next = NULL;
	return (token);
}

t_token	*create_eof_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = T_EOF;
	token->value = NULL;
	token->raw = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **first, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*first)
	{
		*first = new;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token_type	get_op_type(const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (T_DLT);
	if (line[i] == '>' && line[i + 1] == '>')
		return (T_DGT);
	if (line[i] == '<')
		return (T_LT);
	if (line[i] == '>')
		return (T_GT);
	return (T_PIPE);
}
