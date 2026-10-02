/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:37:29 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/17 09:10:23 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next_tmp;

	if (!*lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next_tmp = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = next_tmp;
	}
	*lst = NULL;
}
