/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 13:32:10 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hdoc_limit(t_redir *new, const char *value)
{
	char	*trimmed;

	if (!new || !value || new->type != R_HDOC)
		return (0);
	if (new->raw)
		free(new->raw);
	new->raw = ft_strdup(value);
	if (!new->raw)
		return (0);
	new->hdoc_quoted = has_any_quote(value);
	trimmed = remove_all_quotes(value);
	if (!trimmed)
		return (0);
	if (new->target)
		free(new->target);
	new->target = trimmed;
	return (1);
}

int	add_arg(char ***av, const char *word)
{
	int		size;
	char	**new;

	if (!av || !word)
		return (0);
	size = get_array_size(*av);
	new = malloc(sizeof(char *) * (size +2));
	if (!new)
		return (0);
	copy_array(new, *av, size);
	new[size] = ft_strdup(word);
	if (!new[size])
		return (free(new), 0);
	new[size +1] = NULL;
	if (*av)
		free(*av);
	*av = new;
	return (1);
}

int	parse_word(t_token **token, t_cmds *new)
{
	t_token	*current;

	if (!token || !new)
		return (0);
	while (*token && ((*token)->type == T_WORD))
	{
		current = *token;
		if (!add_arg(&new->args, current->value))
			return (0);
		*token = current->next;
	}
	return (1);
}

int	parse_loop(t_token **token, t_cmds *new)
{
	if (!token || !*token || !new)
		return (0);
	while (*token && (*token)->type != T_PIPE && (*token)->type != T_EOF)
	{
		if (is_redir(*token))
		{
			if (!parse_redir(token, new))
				return (0);
		}
		else if ((*token)->type == T_WORD)
		{
			if (!parse_word(token, new))
				return (0);
		}
		else
			return (msg_error(
					(char *)which_token_error(*token), NULL, NULL, 0));
	}
	return (1);
}

t_cmds	*parse_command(t_token	**token)
{
	t_cmds	*new;

	if (!token || !*token)
		return (NULL);
	new = init_cmd();
	if (!new)
		return (NULL);
	if (!parse_loop(token, new))
		return (free_cmd_list(new), NULL);
	return (new);
}
