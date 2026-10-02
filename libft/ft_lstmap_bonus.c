/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:28:59 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/17 10:02:36 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*tmp;
	t_list	*ntmp;

	newlst = NULL;
	if (!lst || !del || !f)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		ntmp = ft_lstnew(f(tmp->content));
		if (!ntmp)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, ntmp);
		tmp = tmp->next;
	}
	return (newlst);
}
