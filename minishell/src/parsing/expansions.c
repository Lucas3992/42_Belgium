/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:44 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:45 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_words_chain(t_token **last, char **words,
			int start, int size)
{
	int		i;
	t_token	*new_node;

	i = start;
	new_node = NULL;
	while (i < size)
	{
		new_node = insert_word(*last, words[i]);
		if (!new_node)
			return (free_words_tail(words, i, size), 0);
		*last = new_node;
		i++;
	}
	return (1);
}

int	apply_words(t_token *current, char **words, int size, t_token **out_last)
{
	t_token	*last;
	char	*old;
	int		ok;

	last = current;
	old = current->value;
	if (old && old != words[0])
		free(old);
	current->value = words[0];
	if (current->raw)
	{
		free(current->raw);
		current->raw = NULL;
	}
	ok = append_words_chain(&last, words, 1, size);
	if (!ok)
		return (0);
	*out_last = last;
	return (1);
}

int	process_t_step(t_token **f, t_token **prev, t_token **current, t_shell *ms)
{
	int	skip;

	if (!current || !(*current))
		return (1);
	skip = skip_exp(*prev, *current);
	if ((*current)->type == T_WORD && skip == 0)
		return (handle_expandable_word(f, prev, current, ms));
	*prev = *current;
	*current = (*current)->next;
	return (1);
}

int	ultimate_expand_tokens(t_token **tokens, t_shell *ms)
{
	t_token	*prev;
	t_token	*current;

	if (!tokens || !(*tokens) || !ms)
		return (1);
	prev = NULL;
	current = *tokens;
	while (current && current->type != T_EOF)
	{
		if (!(process_t_step(tokens, &prev, &current, ms)))
			return (0);
	}
	return (1);
}
