/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:40:39 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 14:02:01 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd(char **args, t_shell *ms)
{
	t_var	*temp;

	temp = ms->env;
	if (!temp)
		return (1);
	if (args[1])
		return (msg_error("env: '", args[1],
				"': No such file or directory", 127));
	while (temp)
	{
		if (temp->has_eq)
		{
			if (temp->value)
				printf("%s=%s\n", temp->key, temp->value);
			else
				printf("%s=\n", temp->key);
		}
		temp = temp->next;
	}
	return (0);
}
