/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:45:30 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 11:15:19 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_down(t_stack *a)
{
	t_node	*tmp;
	t_node	*last_node;

	if (a && a->size > 1)
	{
		tmp = a->first;
		while (tmp->next != a->last)
			tmp = tmp->next;
		last_node = tmp->next;
		tmp->next = NULL;
		a->last = tmp;
		last_node->next = a->first;
		a->first = last_node;
	}
}

void	rra(t_stack *a)
{
	rotate_down(a);
	write (1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	rotate_down(b);
	write (1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	rotate_down(a);
	rotate_down(b);
	write (1, "rrr\n", 4);
}
