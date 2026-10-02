/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skips.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:25 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:26 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_exp(t_token *prev, t_token *current)
{
	if (!prev || !current)
		return (0);
	if (prev->type == T_DLT && current->type == T_WORD)
		return (1);
	return (0);
}

void	skip_quote(t_exp *ex)
{
	if (!ex->dq && ex->in[ex->i] == '\'')
	{
		ex->sq = !ex->sq;
		ex->quote_flag = 1;
		ex->i++;
	}
	else if (!ex->sq && ex->in[ex->i] == '\"')
	{
		ex->dq = !ex->dq;
		ex->quote_flag = 1;
		ex->i++;
	}
}
