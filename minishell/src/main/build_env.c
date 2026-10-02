/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleyro <dcasiell@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:03 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/14 14:38:11 by sleyro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_free_element(char *key, char *value, t_shell *ms)
{
	if (key)
		free(key);
	if (value)
		free(value);
	msg_error_exit("Error: can't init env.", 1, ms);
}

static void	default_env(t_shell *ms)
{
	char	*path;
	int		status;

	status = 0;
	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup("/");
	if (!path)
		msg_error_exit("Error: can't init default PWD", 1, ms);
	status += env_add_back(ms, "PWD", path, true);
	status += env_add_back(ms, "SHLVL", "1", true);
	status += env_add_back(ms, "PATH", "/usr/bin:/bin", true);
	status += env_add_back(ms, "OLDPWD", NULL, false);
	status += env_add_back(ms, "_", "minishell", true);
	free(path);
	if (status != 0)
		msg_error_exit("Error: can't init env.", 1, ms);
	norm_shlvl(ms);
}

void	create_env(char **env, t_shell *ms)
{
	int		i;
	char	*key;
	char	*value;
	bool	eq;

	if (!env || !env[0])
		return (default_env(ms));
	i = 0;
	while (env[i])
	{
		key = NULL;
		value = NULL;
		eq = false;
		if (parse_env(env[i], &key, &value, &eq) != 0)
			error_free_element(key, value, ms);
		if (env_insert(ms, key, value, eq) != 0)
			error_free_element(key, value, ms);
		free(key);
		free(value);
		i++;
	}
	norm_shlvl(ms);
	check_pwd(ms);
}
