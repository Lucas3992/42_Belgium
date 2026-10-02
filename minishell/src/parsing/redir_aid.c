/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:26:04 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/17 10:23:05 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_redir_target(t_redir *new, t_token *tok)
{
	if (tok->raw)
		new->raw = ft_strdup(tok->raw);
	else
		new->raw = ft_strdup(tok->value);
	if (!new->raw)
		return (0);
	new->target = remove_quotes_from_string(tok->value);
	if (!new->target)
		return (0);
	return (1);
}

int	open_file_redir(t_redir *r, int *fd_in, int *fd_out)
{
	if (r->type == R_IN)
		return (redirect_in(r, fd_in));
	if (r->type == R_OUT)
		return (redirect_out(r, fd_out));
	return (redirect_app(r, fd_out));
}

static int	has_split_ws(const char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	validate_redirect_target(const char *shown, char **target)
{
	if (!target || !*target || **target == '\0')
	{
		write(2, "minishell: ", 11);
		if (shown)
			write(2, shown, ft_strlen(shown));
		write(2, ": ambiguous redirect\n", 21);
		return (1);
	}
	if (has_split_ws(*target))
	{
		write(2, "minishell: ", 11);
		if (shown)
			write(2, shown, ft_strlen(shown));
		write(2, ": ambiguous redirect\n", 21);
		return (1);
	}
	return (0);
}
