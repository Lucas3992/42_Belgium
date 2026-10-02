/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:19 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:20 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_partial(char **env, int filled)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (i < filled)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static int	append_var(char **env, t_var *c_var)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(c_var->key, "=");
	if (!tmp)
		return (1);
	if (c_var->value == NULL)
		res = ft_strdup(tmp);
	else
		res = ft_strjoin(tmp, c_var->value);
	free(tmp);
	if (!res)
		return (1);
	*env = res;
	return (0);
}

char	**var_to_env(t_shell *ms)
{
	t_var	*c_var;
	char	**env;
	size_t	size;
	int		i;

	size = ft_lstsize_eq(ms->env);
	env = (char **)calloc(size + 1, sizeof(*env));
	if (!env)
		return (NULL);
	i = 0;
	c_var = ms->env;
	while (c_var)
	{
		if (c_var->has_eq)
		{
			if (append_var(&env[i], c_var))
				return (free_env_partial(env, i), NULL);
			i++;
		}
		c_var = c_var->next;
	}
	env[i] = NULL;
	return (env);
}
