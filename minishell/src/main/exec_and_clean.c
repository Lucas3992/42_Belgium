/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:07 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 12:16:28 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_exec_and_cleanup(t_shell *ms)
{
	int	status;
	int	code;

	status = exec(ms);
	if (ms->should_exit)
	{
		code = ms->exit_status;
		free_ms(ms, NULL);
		exit(code);
	}
	else
	{
		if (ms->tree)
		{
			free_ast(ms->tree);
			ms->tree = NULL;
		}
	}
	return (status);
}
