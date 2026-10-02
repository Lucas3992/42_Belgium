/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:06 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:07 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_lstlast(t_var *lst)
{
	t_var	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

int	ft_lstsize(t_var *lst)
{
	int		i;
	t_var	*count;

	count = lst;
	i = 0;
	while (count != NULL)
	{
		i++;
		count = count->next;
	}
	return (i);
}

int	ft_lstsize_eq(t_var *lst)
{
	int		i;
	t_var	*count;

	count = lst;
	i = 0;
	while (count != NULL)
	{
		if (count->has_eq)
			i++;
		count = count->next;
	}
	return (i);
}
