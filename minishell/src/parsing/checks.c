/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:32 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 14:16:07 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	is_valid_for_cmd(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_WORD || is_redir(token))
		return (1);
	return (0);
}
