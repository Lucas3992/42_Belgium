/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expandable_word.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:26:15 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 09:26:16 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_after_redir(t_token *prev)
{
	if (!prev)
		return (0);
	if (prev->type == T_LT)
		return (1);
	if (prev->type == T_GT)
		return (1);
	if (prev->type == T_DGT)
		return (1);
	return (0);
}

static int	force_empty_and_advance(t_token **p, t_token **c)
{
	char	*empty;

	empty = ft_strdup("");
	if (!empty)
		return (0);
	if ((*c)->value && (*c)->value != empty)
		free((*c)->value);
	(*c)->value = empty;
	*p = *c;
	*c = (*c)->next;
	return (1);
}

static int	shrink_zero_or_multi_after_redir(int size, t_token **p,
					t_token **c, char **words)
{
	int	ok;

	ok = force_empty_and_advance(p, c);
	if (!ok)
	{
		if (size > 0)
			free_words_tail(words, 0, size);
		else
			free(words);
		return (0);
	}
	if (size > 0)
		free_words_tail(words, 0, size);
	else
		free(words);
	return (1);
}

static int	remove_current_and_fix_cursor(t_token **f, t_token **p, t_token **c)
{
	t_token	*next;

	next = (*c)->next;
	remove_token(f, *p, *c);
	if (!(*p))
		*c = *f;
	else
		*c = next;
	return (1);
}

int	handle_expandable_word(t_token **f, t_token **p, t_token **c, t_shell *ms)
{
	char	**words;
	int		size;
	t_token	*last;

	words = expand_one_token((*c)->value, ms);
	if (!words)
		return (0);
	size = get_array_size(words);
	if (size == 0 && is_after_redir(*p))
		return (shrink_zero_or_multi_after_redir(0, p, c, words));
	if (size == 0)
	{
		free(words);
		return (remove_current_and_fix_cursor(f, p, c));
	}
	if (size > 1 && is_after_redir(*p))
		return (shrink_zero_or_multi_after_redir(size, p, c, words));
	if (!apply_words(*c, words, size, &last))
		return (free(words), 0);
	*p = last;
	*c = last->next;
	return (free(words), 1);
}
