/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_empty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:50 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:47:51 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_empty(t_exp *ex)
{
	if (!ex)
		return (0);
	if (!ex->current)
	{
		ex->current = ft_strdup("");
		if (!ex->current)
			return (0);
	}
	return (1);
}
