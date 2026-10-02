/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:46 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/20 10:28:56 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*free_node_and_return(t_var *node, char *key)
{
	msg_error("Error : can't create new var", NULL, NULL, 1);
	if (key)
		free(key);
	if (node)
		free(node);
	return (NULL);
}

void	free_var_list(t_var **first)
{
	t_var	*cur;
	t_var	*next;

	if (!first || !*first)
		return ;
	cur = *first;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*first = NULL;
}

static int	handle_cd_errno(char *target)
{
	char	*msg;

	msg = NULL;
	if (target)
	{
		msg = ft_strjoin(target, ": ");
		free(target);
	}
	msg_error("cd: ", msg, strerror(errno), 1);
	if (msg)
		free(msg);
	return (1);
}

int	free_pwd_and_msg(char *oldpwd, char *target, int code, char *args)
{
	const char	*orig;

	orig = args;
	if (oldpwd)
		free(oldpwd);
	if (code == 2)
		return (handle_cd_errno(target));
	if (target)
		free(target);
	if (code == 1)
	{
		if (orig && ft_strcmp(orig, "-") == 0)
			return (msg_error("cd: ", NULL, "OLDPWD not set", 1));
		return (msg_error("cd: ", NULL, "HOME not set", 1));
	}
	if (code == 3)
		return (msg_error("cd: ", NULL, "failed to update PWD/OLDPWD", 1));
	return (msg_error("cd: ", NULL, "unexpected error", 1));
}
