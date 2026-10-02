/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:14 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 10:17:29 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_hostname(void)
{
	int		fd;
	int		i;
	char	*buffer;
	ssize_t	is_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 1)
		return (NULL);
	buffer = malloc(_SC_HOST_NAME_MAX + 1);
	if (!buffer)
		return (NULL);
	is_read = read(fd, buffer, _SC_HOST_NAME_MAX);
	close(fd);
	if (is_read <= 0)
		return (free(buffer), NULL);
	if (is_read > 0 && buffer[is_read - 1] == '\n')
		buffer[is_read - 1] = '\0';
	else
		buffer[is_read] = '\0';
	i = 0;
	while (buffer [i] && buffer[i] != '.')
		i++;
	buffer[i] = ':';
	buffer[i + 1] = '\0';
	return (buffer);
}

static char	*replace_home(char *path_with_home, t_shell *ms)
{
	char	*home_path;
	size_t	len_home;
	size_t	len_path;
	t_var	*home;

	home = env_find_key(ms->env, "HOME");
	if (home && home->value)
		home_path = home->value;
	else
		home_path = getenv("HOME");
	if (!home_path)
		return (ft_strdup(path_with_home));
	len_home = ft_strlen(home_path);
	len_path = ft_strlen(path_with_home);
	if (len_path >= len_home
		&& ft_strncmp(path_with_home, home_path, len_home) == 0
		&& (path_with_home[len_home] == 0 || path_with_home[len_home] == '/'))
	{
		if (len_path == len_home)
			return (ft_strdup("~"));
		return (ft_strjoin("~", path_with_home + len_home));
	}
	return (ft_strdup(path_with_home));
}

static char	*join_prompt(char *final_path, char *host, char *home)
{
	if (!host)
		host = ft_strdup("");
	if (!home)
		home = ft_strdup("");
	final_path = ft_strjoin_free(final_path, "@", 1, 0);
	final_path = ft_strjoin_free(final_path, host, 1, 1);
	final_path = ft_strjoin_free(final_path, home, 1, 1);
	final_path = ft_strjoin_free(final_path, "$ ", 1, 0);
	return (final_path);
}

static char	*display_prompt(t_shell *ms)
{
	t_var	*path_var;
	t_var	*user;
	char	*final_path;
	char	*home;
	char	*host;

	path_var = env_find_key(ms->env, "PWD");
	user = env_find_key(ms->env, "USER");
	if (user && user->value)
		final_path = ft_strdup(user->value);
	else
		final_path = ft_strdup("user");
	if (!final_path)
		return (NULL);
	host = get_hostname();
	home = NULL;
	if (path_var && path_var->value)
		home = replace_home(path_var->value, ms);
	else
		home = ft_strdup("");
	final_path = join_prompt(final_path, host, home);
	return (final_path);
}

int	get_line_and_history(t_shell *ms, char **out)
{
	char	*prompt;

	prompt = NULL;
	*out = NULL;
	setup_signals();
	prompt = display_prompt(ms);
	*out = readline(prompt);
	free(prompt);
	if (!*out)
	{
		write(1, "exit\n", 5);
		free_ms(ms, NULL);
		return (0);
	}
	ms->last_exit_code = update_last_ms_exit_code(ms);
	if ((*out)[0] != '\0')
		add_history(*out);
	return (1);
}
