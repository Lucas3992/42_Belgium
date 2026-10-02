/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:38 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:39 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*cut_in_operator_token(const char *line, int i)
{
	t_token			*token;
	t_token_type	t_type;

	if (!line)
		return (NULL);
	t_type = get_op_type(line, i);
	token = create_op_token(t_type);
	return (token);
}

t_token	*cut_in_word_tokens(const char *line, int start, int end)
{
	int		size;
	char	*t;
	t_token	*token;

	if (!line || end < start)
		return (NULL);
	size = end - start;
	t = ft_substr(line, (unsigned int)start, (unsigned int)size);
	if (!t)
		return (NULL);
	token = create_word_token(t);
	if (!token)
		return (NULL);
	return (token);
}

t_token	*tokenize_line(const char *line)
{
	int		i;
	int		next;
	t_token	*first;
	t_token	*eof;	

	if (!line)
		return (NULL);
	first = NULL;
	i = 0;
	while (line[i])
	{
		i = i + skip_spaces(line, i);
		if (!line[i])
			break ;
		next = add_word_or_op(line, i, &first);
		if (next < 0)
			return (free_tokens(first), NULL);
		i = next;
	}
	eof = create_eof_token();
	if (!eof)
		return (free_tokens(first), NULL);
	add_token(&first, eof);
	return (first);
}
