/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_or_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:46:14 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/09 13:23:19 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack *a)
{
	if (a->first->value > a->first->next->value)
		sa(a);
}

void	sort_three(t_stack *a)
{
	int	x;
	int	y;
	int	z;

	x = a->first->value;
	y = a->first->next->value;
	z = a->last->value;
	if (x > y && y < z && z > x)
		sa(a);
	else if (x > y && y > z)
	{
		sa(a);
		rra(a);
	}
	else if (x > y && y < z && z < x)
		ra(a);
	else if (x < y && y > z && z > x)
	{
		sa(a);
		ra(a);
	}
	else if (x < y && y > z && z < x)
		rra(a);
}
