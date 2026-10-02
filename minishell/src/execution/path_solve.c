/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:37 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/20 13:18:45 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_slash(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_directory(char *path)
{
	struct stat	st;
	int			ret;

	ret = stat(path, &st);
	if (ret == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

int	is_executable(char *path)
{
	if (is_directory(path))
		return (0);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*join_path(char *dir, char *cmd)
{
	int		size_dir;
	int		size_cmd;
	char	*out;

	size_cmd = ft_strlen(cmd);
	size_dir = ft_strlen(dir);
	out = malloc(size_cmd +1 + size_dir +1);
	if (!out)
		return (NULL);
	ft_memcpy(out, dir, size_dir);
	out[size_dir] = '/';
	ft_memcpy(out + size_dir +1, cmd, size_cmd);
	out[size_dir +1 + size_cmd] = '\0';
	return (out);
}

char	*resolve_command_path(t_shell *ms, t_cmds *cmd, int *error_code)
{
	char	*name;
	char	*path;

	*error_code = 0;
	if (!cmd || !cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		*error_code = 127;
		return (NULL);
	}
	name = cmd->args[0];
	if (has_slash(name))
	{
		path = classify_direct_path(name, error_code);
		return (path);
	}
	path = get_full_path(ms, cmd);
	if (!path)
		if_no_path(name, ms, error_code);
	ms->last_exit_code = *error_code;
	return (path);
}
