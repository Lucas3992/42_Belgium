/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:26 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/17 11:40:28 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable_file(const char *path)
{
	struct stat	st;
	int			ret;

	ret = stat(path, &st);
	if (ret == 0 && !S_ISDIR(st.st_mode) && access(path, X_OK) == 0)
		return (1);
	return (0);
}

static char	*join_dir_cmd(const char *dir, const char *cmd)
{
	int		ld;
	int		lc;
	char	*s;

	if (!cmd)
		return (NULL);
	if (!dir || dir[0] == '\0')
		return (ft_strdup(cmd));
	ld = ft_strlen(dir);
	lc = ft_strlen(cmd);
	s = (char *)malloc(ld + 1 + lc + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, dir, ld);
	s[ld] = '/';
	ft_memcpy(s + ld + 1, cmd, lc);
	s[ld + 1 + lc] = '\0';
	return (s);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*full;
	int		i;

	if (!cmd || !cmd[0] || !paths)
		return (NULL);
	i = 0;
	full = NULL;
	while (paths[i])
	{
		full = join_dir_cmd(paths[i], cmd);
		if (!full)
			return (NULL);
		if (is_executable_file(full))
			return (full);
		free(full);
		full = NULL;
		i++;
	}
	return (NULL);
}

char	*get_full_path(t_shell *ms, t_cmds *cmd)
{
	char	**paths;
	char	*cmd_path;
	t_var	*path;

	if (has_slash(cmd->args[0]))
		return (ft_strdup(cmd->args[0]));
	path = env_find_key(ms->env, "PATH");
	if (!path || !path->has_eq || !path->value || path->value[0] == '\0')
		return (NULL);
	paths = ft_split(path->value, ':');
	cmd_path = get_cmd_path(cmd->args[0], paths);
	if (!cmd_path)
		return (free_array(paths), NULL);
	cmd->builtin = false;
	free_array(paths);
	return (cmd_path);
}

char	*classify_direct_path(char *path, int *error_code)
{
	struct stat	st;
	int			ret;

	*error_code = 0;
	ret = stat(path, &st);
	if (ret == -1)
	{
		*error_code = 127;
		return (NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		*error_code = 126;
		return (NULL);
	}
	if (access(path, X_OK))
	{
		*error_code = 126;
		return (NULL);
	}
	return (ft_strdup(path));
}
