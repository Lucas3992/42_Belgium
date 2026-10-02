/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:13 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:14 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_str(t_exp *ex, char *str)
{
	char	**tmp;
	int		i;

	if (!ex || !str)
		return (0);
	tmp = malloc(sizeof(char *) * (ex->out_len +2));
	if (!tmp)
		return (0);
	i = 0;
	while (i < ex->out_len)
	{
		tmp[i] = ex->out[i];
		i++;
	}
	tmp[i] = str;
	tmp[i +1] = NULL;
	if (ex->out != NULL)
		free(ex->out);
	ex->out = tmp;
	ex->out_len++;
	return (1);
}
