/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:35 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:36 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && is_space(str[i]))
		i++;
	return (i - start);
}

static int	find_word_end(const char *line, int i)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (line[i])
	{
		if (!dq && line[i] == '\'')
			sq = !sq;
		else if (!sq && line[i] == '\"')
			dq = !dq;
		else if (!sq && !dq && (is_space(line[i]) || is_operator(line[i])))
			break ;
		i++;
	}
	if (sq || dq)
		return (-1);
	return (i);
}

static int	get_op_size(const char *line, int i)
{
	if (!line || !line[i])
		return (0);
	if (line[i] == '<' && line[i + 1] == '<')
		return (2);
	if (line[i] == '>' && line[i + 1] == '>')
		return (2);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

int	add_word_or_op(const char *line, int i, t_token **first)
{
	int		len;
	int		end;
	t_token	*token;

	if (is_operator(line[i]))
	{
		len = get_op_size(line, i);
		token = cut_in_operator_token(line, i);
		if (!token)
			return (-1);
		add_token(first, token);
		return (i + len);
	}
	end = find_word_end(line, i);
	if (end == -1)
		return (-1);
	token = cut_in_word_tokens(line, i, end);
	if (!token)
		return (-1);
	add_token(first, token);
	return (end);
}
