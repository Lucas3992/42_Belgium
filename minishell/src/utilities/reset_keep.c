/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_keep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:19 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:20 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*reset_and_keep_str(t_exp *ex)
{
	char	*str;

	if (!ex)
		return (NULL);
	str = ex->current;
	ex->current = NULL;
	return (str);
}

char	**reset_and_keep_array(t_exp *ex)
{
	char	**arr;
	char	**empty;

	if (!ex)
		return (NULL);
	arr = ex->out;
	ex->out = NULL;
	ex->out_len = 0;
	if (!arr)
	{
		empty = malloc(sizeof(char *));
		if (!empty)
			return (NULL);
		empty[0] = NULL;
		return (empty);
	}
	return (arr);
}
