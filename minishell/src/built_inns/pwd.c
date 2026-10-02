/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:04 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:41:05 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_shell *ms)
{
	char	*path;
	t_var	*pwd_var;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		ms->last_exit_code = 0;
		return (0);
	}
	pwd_var = env_find_key(ms->env, "PWD");
	if (pwd_var && pwd_var->has_eq && pwd_var->value)
	{
		printf("%s\n", pwd_var->value);
		ms->last_exit_code = 0;
		return (0);
	}
	ms->last_exit_code = 1;
	return (1);
}
