/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:49:52 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 16:14:30 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*copy_stack_in_int_array(t_stack *a)
{
	int		*array;
	int		i;
	t_node	*tmp;

	array = malloc(a->size * sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	tmp = a->first;
	while (tmp)
	{
		array[i] = tmp->value;
		i++;
		tmp = tmp->next;
	}
	return (array);
}

static int	*sort_array(int *array, int size)
{
	int	i;
	int	j;
	int	tmp;

	if (!array || size <= 1)
		return (array);
	i = 0;
	while (i < size -1)
	{
		j = 0;
		while (j < size - i -1)
		{
			if (array[j] > array[j +1])
			{
				tmp = array[j];
				array[j] = array[j +1];
				array[j +1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

static void	assign_index_to_stack(t_stack *a, int *sorted_array)
{
	t_node	*tmp;
	int		i;

	if (!a || !sorted_array)
		return ;
	tmp = a->first;
	while (tmp)
	{
		i = 0;
		while (i < a->size)
		{
			if (tmp->value == sorted_array[i])
			{
				tmp->index = i;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

int	find_next_chunk_index(t_stack *a, int min, int max)
{
	int		i;
	t_node	*tmp;

	if (!a || !a->first)
		return (-1);
	i = 0;
	tmp = a->first;
	while (tmp)
	{
		if (tmp->index >= min && tmp->index <= max)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

void	index_stack(t_stack *a)
{
	int	*array;

	array = copy_stack_in_int_array(a);
	sort_array(array, a->size);
	assign_index_to_stack(a, array);
	free(array);
}
