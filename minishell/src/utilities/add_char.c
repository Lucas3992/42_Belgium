/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:41 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:47:41 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_char(t_exp *ex, char c)
{
	int		i;
	int		size;
	char	*tmp;

	if (!dup_empty(ex))
		return (0);
	size = ft_strlen(ex->current);
	tmp = malloc(size +2);
	if (!tmp)
		return (0);
	i = 0;
	while (i < size)
	{
		tmp[i] = ex->current[i];
		i++;
	}
	tmp[size] = c;
	tmp[size +1] = '\0';
	free(ex->current);
	ex->current = tmp;
	return (1);
}
