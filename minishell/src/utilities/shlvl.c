/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:22 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:23 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reduce_shlvl(int n)
{
	if (n <= 0 || n > 1000)
		return (1);
	return ((int)n);
}

void	norm_shlvl(t_shell *ms)
{
	int		n;
	t_var	*shlvl;
	char	*lvl;

	shlvl = env_find_key(ms->env, "SHLVL");
	n = ft_atoi(shlvl->value);
	n += 1;
	n = reduce_shlvl(n);
	lvl = ft_itoa(n);
	if (!lvl)
		msg_error_exit("Error: SHLVL alloc fail.", 1, ms);
	if (env_value_update(shlvl, lvl) != 0)
	{
		free(lvl);
		msg_error_exit("Error: SHLVL update", 1, ms);
	}
	shlvl->has_eq = true;
	free(lvl);
}
