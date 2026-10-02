/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:29 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:30 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_env_value(t_var *env, const char *key, int size_key)
{
	t_var	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, key, (size_t)size_key) == 0
			&& current->key[size_key] == '\0')
		{
			if (current->value != NULL)
				return (ft_strdup(current->value));
			return (ft_strdup(""));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*transform_dollar_value(t_exp *ex, int len, int qmark)
{
	char	*value;

	value = NULL;
	if (qmark)
		value = ft_itoa(ex->last_status);
	else
		value = dup_env_value(ex->env, ex->in + ex->i +1, len);
	if (!value)
		value = ft_strdup("");
	return (value);
}
