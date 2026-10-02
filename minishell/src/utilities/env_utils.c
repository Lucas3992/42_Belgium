/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:53 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:47:54 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*env_find_key(t_var *list, const char *key)
{
	t_var	*temp;

	if (!key || key[0] == '\0' || !list)
		return (NULL);
	temp = list;
	while (temp)
	{
		if (ft_strcmp(temp->key, (char *)key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	env_value_update(t_var *node, const char *value)
{
	char	*temp;

	if (!node)
		return (1);
	if ((node->value == NULL && value == NULL)
		|| (node->value && value && ft_strcmp(node->value, (char *)value) == 0))
		return (0);
	temp = NULL;
	if (value)
	{
		temp = ft_strdup(value);
		if (!temp)
			return (1);
	}
	free(node->value);
	node->value = temp;
	return (0);
}

t_var	*env_new_pair(const char *key, const char *value, bool eq)
{
	t_var	*new;

	if (!key || key[0] == '\0')
		return (NULL);
	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	new->value = NULL;
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	new->has_eq = eq;
	return (new);
}

int	env_add_back(t_shell *ms, const char *key, const char *value, bool eq)
{
	t_var	*temp;
	t_var	*new_var;

	if (!ms || !key || key[0] == '\0')
		return (1);
	new_var = env_new_pair(key, value, eq);
	if (!new_var)
		return (1);
	if (!ms->env)
		ms->env = new_var;
	else
	{
		temp = ft_lstlast(ms->env);
		temp->next = new_var;
		new_var->prev = temp;
	}
	return (0);
}

int	env_insert(t_shell *ms, const char *key, const char *value, bool eq)
{
	t_var	*to_insert;

	to_insert = env_find_key(ms->env, key);
	if (!to_insert)
		return (env_add_back(ms, key, value, eq));
	if (!eq)
		return (0);
	to_insert->has_eq = true;
	return (env_value_update(to_insert, value));
}
