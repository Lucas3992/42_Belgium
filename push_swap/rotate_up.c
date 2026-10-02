/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:38:13 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 11:04:17 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_up(t_stack *a)
{
	t_node	*tmp;

	if (a && a->size > 1)
	{
		tmp = a->first;
		a->first = tmp->next;
		a->last->next = tmp;
		a->last = tmp;
		a->last->next = NULL;
	}
}

void	ra(t_stack *a)
{
	rotate_up(a);
	write (1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	rotate_up(b);
	write (1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	rotate_up(a);
	rotate_up(b);
	write (1, "rr\n", 3);
}
