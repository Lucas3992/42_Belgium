/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:22:44 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/09 11:56:42 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_top_two(t_stack *a)
{
	t_node	*first_a;
	t_node	*second_a;
	int		tmp;

	if (a && a->size >= 2)
	{
		first_a = a->first;
		second_a = first_a->next;
		tmp = first_a->value;
		first_a->value = second_a->value;
		second_a->value = tmp;
	}
}

void	sa(t_stack *a)
{
	swap_top_two(a);
	write (1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	swap_top_two(b);
	write (1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	swap_top_two(a);
	swap_top_two(b);
	write (1, "ss\n", 3);
}
