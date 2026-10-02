/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:51 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 13:05:11 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ex(t_exp *ex)
{
	int	i;

	if (!ex)
		return ;
	if (ex->current)
		free(ex->current);
	if (ex->out)
	{
		i = 0;
		while (ex->out[i])
		{
			free(ex->out[i]);
			i++;
		}
		free(ex->out);
	}
}

int	cleanup(t_exec *ex, int status)
{
	close_fd_redirect(&ex->fd_in, &ex->fd_out);
	restore_stdio(ex);
	ex->ms->last_exit_code = status;
	return (status);
}
