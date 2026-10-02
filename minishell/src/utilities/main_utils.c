/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleyro <dcasiell@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:09 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/14 15:10:51 by sleyro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pwd(t_shell *ms)
{
	t_var	*pwd;
	char	*cwd;
	int		ret;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	if (!cwd)
		return (1);
	pwd = env_find_key(ms->env, "PWD");
	if (pwd && pwd->value && ft_strcmp(pwd->value, cwd) == 0)
	{
		free(cwd);
		return (0);
	}
	ret = env_insert(ms, "PWD", cwd, 1);
	free(cwd);
	return (ret != 0);
}

static t_bi	bi_type(const char *s)
{
	if (!s)
		return (T_NOT_BUILTIN);
	if (ft_strcmp(s, "echo") == 0)
		return (T_ECHO);
	if (ft_strcmp(s, "cd") == 0)
		return (T_CD);
	if (ft_strcmp(s, "env") == 0)
		return (T_ENV);
	if (ft_strcmp(s, "exit") == 0)
		return (T_EXIT);
	if (ft_strcmp(s, "export") == 0)
		return (T_EXPORT);
	if (ft_strcmp(s, "pwd") == 0)
		return (T_PWD);
	if (ft_strcmp(s, "unset") == 0)
		return (T_UNSET);
	if (ft_strcmp(s, ".") == 0)
		return (T_DOT);
	return (T_NOT_BUILTIN);
}

void	is_builtin(t_shell *ms, t_cmds *cmd)
{
	t_bi	t;
	char	*tmp;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	cmd->builtin = false;
	t = bi_type(cmd->args[0]);
	if (t == T_ENV && path_unset_or_empty(ms))
		t = T_NOT_BUILTIN;
	if (t != T_NOT_BUILTIN)
	{
		cmd->type = t;
		cmd->builtin = true;
		return ;
	}
	if (ft_strchr(cmd->args[0], '/'))
	{
		cmd->type = T_NOT_BUILTIN;
		return ;
	}
	tmp = get_full_path(ms, cmd);
	if (tmp)
		free(tmp);
	cmd->type = T_NOT_BUILTIN;
}
