/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:33:09 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/13 13:06:36 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_node(t_stack *src, t_stack *dst)
{
	t_node	*node_to_push;

	if (src && src->size > 0)
	{
		node_to_push = src->first;
		src->first = node_to_push->next;
		if (src->first == NULL)
			src->last = NULL;
		src->size--;
		node_to_push->next = dst->first;
		dst->first = node_to_push;
		if (dst->size == 0)
			dst->last = node_to_push;
		dst->size++;
	}
}

void	pa(t_stack *a, t_stack *b)
{
	push_node(b, a);
	write (1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	push_node(a, b);
	write (1, "pb\n", 3);
}
