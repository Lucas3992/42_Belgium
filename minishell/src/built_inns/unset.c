/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleyro <dcasiell@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:09 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/14 15:24:03 by sleyro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_remove_node(t_var **head, t_var *node)
{
	if (!head || !*head || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
	node = NULL;
}

static void	unset_loop(t_shell *ms, const char *key)
{
	t_var	*cur;

	cur = env_find_key(ms->env, key);
	while (cur != NULL)
	{
		unset_remove_node(&ms->env, cur);
		cur = env_find_key(ms->env, key);
	}
}

int	unset(char **args, t_shell *ms)
{
	int		i;

	if (ft_strcmp(args[0], "unset"))
		return (msg_error("Wrong command:", args[0], "isn't unset", 1));
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		unset_loop(ms, args[i]);
		i++;
	}
	return (0);
}
