/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:01 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 12:27:34 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **args, t_shell *ms)
{
	int	i;
	int	status;
	int	ret;

	status = 0;
	if (ft_strcmp(args[0], "export"))
		return (msg_error("Wrong command:",
				args[0], "isn't export", 1));
	if (!args[1])
		return (export_no_args(ms));
	i = 1 ;
	while (args[i])
	{
		ret = export_loop(args, ms, i);
		if (ret != 0)
			status = ret;
		i++;
	}
	ms->last_exit_code = status;
	return (status);
}

int	export_loop(char **args, t_shell *ms, int i)
{
	char	*key;
	char	*value;
	bool	eq;
	int		status;

	if (!is_valid_var(args[i]))
		return (msg_error("export: '",
				args[i], "': not a valid identifier", 1));
	if (parse_env(args[i], &key, &value, &eq) != 0)
		return (1);
	status = env_insert(ms, key, value, eq);
	free(key);
	if (value)
		free(value);
	return (status);
}
