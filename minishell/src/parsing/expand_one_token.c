/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:41 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:42 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_char(t_exp *ex)
{
	if (!(add_char(ex, ex->in[ex->i])))
		return (0);
	ex->i = ex->i +1;
	return (1);
}

static int	process_step(t_exp *ex)
{
	if (ex->in[ex->i] == '\'' && ex->dq == 0)
		return (skip_quote(ex), 1);
	if (ex->in[ex->i] == '\"' && ex->sq == 0)
		return (skip_quote(ex), 1);
	if (ex->in[ex->i] == '$' && ex->sq == 0)
		return (handle_dollar(ex));
	return (handle_char(ex));
}

static void	free_and_null(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

static int	finalize_ex(t_exp *ex)
{
	char	*taken;
	char	*empty;

	if (!ex)
		return (0);
	if (ex->current != NULL && ex->current[0] != '\0')
	{
		taken = reset_and_keep_str(ex);
		if (!taken)
			return (0);
		if (!push_str(ex, taken))
			return (free(taken), 0);
		free_and_null(&ex->current);
	}
	else if (ex->quote_flag != 0)
	{
		empty = ft_strdup("");
		if (!empty)
			return (0);
		if (!push_str(ex, empty))
			return (free(empty), 0);
	}
	else
		free_and_null(&ex->current);
	return (1);
}

char	**expand_one_token(const char *str, t_shell *ms)
{
	t_exp	ex;

	init_exp(&ex, ms, (char *)str);
	while (ex.in[ex.i])
	{
		if (!process_step(&ex))
			return (free_ex(&ex), NULL);
	}
	if (!(finalize_ex(&ex)))
		return (free_ex(&ex), NULL);
	return (reset_and_keep_array(&ex));
}
