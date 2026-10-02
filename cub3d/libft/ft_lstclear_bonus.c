/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:02:32 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/13 09:37:46 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tempdel;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tempdel = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tempdel;
	}
}
