/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_from_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:15:34 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/25 10:10:13 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_max_index(t_stack *b)
{
	t_node	*tmp;
	int		max;

	if (!b || !b->first)
		return (-1);
	tmp = b->first;
	max = b->first->index;
	while (tmp)
	{
		if (tmp->index > max)
			max = tmp->index;
		tmp = tmp->next;
	}
	return (max);
}

static int	find_position_of_index_max(t_stack *b, int index_max)
{
	int		i;
	t_node	*tmp;

	if (!b || !b->first)
		return (-1);
	i = 0;
	tmp = b->first;
	while (tmp)
	{
		if (tmp->index == index_max)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	find_min_value(t_stack *a)
{
	t_node	*tmp;
	int		min;

	if (!a || !a->first)
		return (-1);
	tmp = a->first;
	min = a->first->value;
	while (tmp)
	{
		if (tmp->value < min)
			min = tmp->value;
		tmp = tmp->next;
	}
	return (min);
}

int	find_position_min_value(t_stack *a)
{
	int		i;
	int		min;
	t_node	*tmp;

	if (!a || !a->first)
		return (-1);
	i = 0;
	min = find_min_value(a);
	tmp = a->first;
	while (tmp)
	{
		if (tmp->value == min)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	fill_a_from_b(t_stack *a, t_stack *b)
{
	int	index_max;
	int	position_index_max;
	int	rotations;

	if (!b || !b->first)
		return ;
	while (b->size > 0)
	{
		index_max = find_max_index(b);
		position_index_max = find_position_of_index_max(b, index_max);
		if (position_index_max <= b->size / 2)
		{
			rotations = position_index_max;
			while (rotations-- > 0)
				rb(b);
		}
		else
		{
			rotations = b->size - position_index_max;
			while (rotations-- > 0)
				rrb(b);
		}
		pa(a, b);
	}
}
