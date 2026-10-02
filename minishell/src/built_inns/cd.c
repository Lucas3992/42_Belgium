/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:40:29 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/20 10:05:53 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_oldpwd(t_shell *ms)
{
	char	*oldpwd;
	t_var	*var_pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		var_pwd = env_find_key(ms->env, "PWD");
		if (!var_pwd || !var_pwd->has_eq || !var_pwd->value)
		{
			oldpwd = ft_strdup("");
			if (!oldpwd)
				return (NULL);
			return (oldpwd);
		}
		oldpwd = ft_strdup(var_pwd->value);
		if (!oldpwd)
			return (NULL);
	}
	return (oldpwd);
}

static char	*get_value(t_shell *ms, const char *key)
{
	t_var	*to_find;

	to_find = env_find_key(ms->env, key);
	if (!to_find || !to_find->has_eq || !to_find->value)
		return (NULL);
	return (to_find->value);
}

static char	*find_target(t_shell *ms, char **args, int *flag)
{
	char	*target;

	*flag = 0;
	if (!args[1] || args[1][0] == '\0' || !ft_strcmp(args[1], "~"))
		target = get_value(ms, "HOME");
	else if (!ft_strcmp(args[1], "-"))
	{
		target = get_value(ms, "OLDPWD");
		*flag = 1;
	}
	else if (args[1][0] == '~' && args[1][1] == '/')
	{
		target = get_value(ms, "HOME");
		if (!target)
			return (NULL);
		return (ft_strjoin(target, args[1] + 1));
	}
	else
		target = args[1];
	if (!target)
		return (NULL);
	return (ft_strdup(target));
}

static int	update_pwds(t_shell *ms, char *oldpwd)
{
	char	*newpwd;
	int		status;

	newpwd = getcwd(NULL, 0);
	status = 0;
	if (!oldpwd)
		oldpwd = "";
	if (!newpwd)
	{
		ft_puterr("cd: error retrieving current directory: getcwd: cannot ");
		ft_puterr("access parent directories: No such file or directory\n");
		status |= env_insert(ms, "OLDPWD", oldpwd, true);
		return (0);
	}
	status |= env_insert(ms, "OLDPWD", oldpwd, true);
	status |= env_insert(ms, "PWD", newpwd, true);
	free(newpwd);
	return (status != 0);
}

int	cd(char **args, t_shell *ms)
{
	char	*target;
	char	*oldpwd;
	int		flag;
	int		status;
	int		ac;

	ac = get_array_size(args);
	if (ac > 2)
		return (msg_error("Too many arguments", NULL, NULL, 1));
	oldpwd = check_oldpwd(ms);
	if (!oldpwd)
		return (1);
	target = find_target(ms, args, &flag);
	if (!target)
		return (free_pwd_and_msg(oldpwd, target, 1, args[1]));
	status = chdir(target);
	if (status != 0)
		return (free_pwd_and_msg(oldpwd, target, 2, NULL));
	if (update_pwds(ms, oldpwd) != 0)
		return (free_pwd_and_msg(oldpwd, target, 3, NULL));
	if (flag)
		if_flag();
	free(oldpwd);
	free(target);
	return (0);
}
