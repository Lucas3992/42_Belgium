/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:29:14 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/24 14:52:28 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_and_push(t_stack *a, t_stack *b, int min, int max)
{
	int	chunk_size;

	if (!a || !b)
		return (0);
	chunk_size = calculate_chunk_range(min, max);
	if (a->first->index <= max && a->first->index >= min)
	{
		pb(a, b);
		if (b->size > 1 && b->first->index < min + (chunk_size / 2))
			rb(b);
		return (1);
	}
	return (0);
}

static void	send_chunk_to_b(t_stack *a, t_stack *b, int min, int max)
{
	int	i;

	i = find_next_chunk_index(a, min, max);
	while (i != -1)
	{
		if (i == 0)
			check_and_push(a, b, min, max);
		else if (i <= a->size / 2)
		{
			while (i-- > 0)
				ra(a);
		}
		else
		{
			while (i++ < a->size)
				rra(a);
		}
		i = find_next_chunk_index(a, min, max);
	}
}

void	all_chunks_to_b(t_stack *a, t_stack *b, int min, int max)
{
	int	how_many_chunks;
	int	chunk_size;
	int	rest;
	int	i;

	if (a->size <= 10)
		how_many_chunks = 4;
	else if (a->size <= 100)
		how_many_chunks = 5;
	else
		how_many_chunks = 11;
	chunk_size = a->size / how_many_chunks;
	rest = a->size % how_many_chunks;
	i = 0;
	while (i < how_many_chunks)
	{
		min = calculate_chunk_start(i, chunk_size, rest);
		max = calculate_chunk_end(i, chunk_size, rest, min);
		send_chunk_to_b(a, b, min, max);
		i++;
	}
}
