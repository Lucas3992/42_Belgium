/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:03 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:04 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_strings(t_exp *ex, const char *str)
{
	char	*tmp;

	if (!dup_empty(ex))
		return (0);
	if (!str)
		return (1);
	tmp = ft_strjoin(ex->current, str);
	if (!tmp)
		return (0);
	free(ex->current);
	ex->current = tmp;
	return (1);
}
