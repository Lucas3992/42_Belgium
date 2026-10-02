/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:47 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:47:47 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	consume_pipe(t_token **token)
{
	if (!token || !*token)
		return (0);
	if ((*token)->type == T_PIPE)
	{
		*token = (*token)->next;
		return (1);
	}
	return (0);
}
