/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:10:17 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 15:28:33 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calculate_chunk_start(int i, int chunk_size, int rest)
{
	int	start;

	start = i * chunk_size;
	if (i < rest)
		start = start + i;
	else
		start = start + rest;
	return (start);
}

int	calculate_chunk_end(int i, int chunk_size, int rest, int start)
{
	int	end;

	if (i < rest)
		end = start + chunk_size;
	else
		end = start + chunk_size -1;
	return (end);
}

int	calculate_chunk_range(int start, int end)
{
	int	chunk_range;

	chunk_range = end - start +1;
	return (chunk_range);
}
